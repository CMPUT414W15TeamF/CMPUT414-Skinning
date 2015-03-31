/*
Copyright (c) 2007 Ilya Baran

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <FL/fl_ask.H>
#include <fstream>

#include "processor.h"
#include "../Pinocchio/skeleton.h"
#include "../Pinocchio/utils.h"
#include "../Pinocchio/debugging.h"
#include "../Pinocchio/attachment.h"
#include "../Pinocchio/pinocchioApi.h"
#include "defmesh.h"
#include "motion.h"

struct ArgData
{
    ArgData() :
        stopAtMesh(false), stopAfterCircles(false), skelScale(1.), noFit(false),
        skeleton(HumanSkeleton())
    {
    }
    
    bool stopAtMesh;
    bool stopAfterCircles;
    string filename;
    string motionname;
    Quaternion<> meshTransform;
    double skelScale;
    bool noFit;
    Skeleton skeleton;
    string skeletonname;
    int skinAlgorithm;	// Indicates which skinning algorithm to use
    float blendWeight;	// Indicates the blending weight for MIX algorithm
};

void printUsageAndExit()
{
    cout << "Usage: DemoUI filename.{obj | ply | off | gts | stl}" << endl;
    cout << "              [-skel skelname] [-rot x y z deg]* [-scale s]" << endl;
    cout << "              [-meshonly | -mo] [-circlesonly | -co]" << endl;
    cout << "              [-motion motionname] [-nofit]" << endl;
    cout << "              [-algo skinning_algorithm [blend_weight]]" << endl;

    exit(0);
}

ArgData processArgs(const vector<string> &args)
{
    ArgData out;
    int cur = 2;
    int num = args.size();
    if(num < 2)
        printUsageAndExit();

    out.filename = args[1];
    // set default skinning algorithm as LBS, and the default blending weight
	// as 0.5
    out.skinAlgorithm = Mesh::LBS;
    out.blendWeight = 0.5;

    while(cur < num) {
        string curStr = args[cur++];
        if(curStr == string("-skel")) {
            if(cur == num) {
                cout << "No skeleton specified; ignoring." << endl;
                continue;
            }
            curStr = args[cur++];
            if(curStr == string("human"))
                out.skeleton = HumanSkeleton();
            else if(curStr == string("horse"))
                out.skeleton = HorseSkeleton();
            else if(curStr == string("quad"))
                out.skeleton = QuadSkeleton();
            else if(curStr == string("centaur"))
                out.skeleton = CentaurSkeleton();
            else
                out.skeleton = FileSkeleton(curStr);
            out.skeletonname = curStr;
        } else if(curStr == string("-rot")) {
            if(cur + 3 >= num) {
                cout << "Too few rotation arguments; exiting." << endl;
                printUsageAndExit();
            }
            double x, y, z, deg;
            sscanf(args[cur++].c_str(), "%lf", &x);
            sscanf(args[cur++].c_str(), "%lf", &y);
            sscanf(args[cur++].c_str(), "%lf", &z);
            sscanf(args[cur++].c_str(), "%lf", &deg);
            
            out.meshTransform = Quaternion<>(Vector3(x, y, z), deg * M_PI / 180.) * out.meshTransform;
        } else if(curStr == string("-scale")) {
            if(cur >= num) {
                cout << "No scale provided; exiting." << endl;
                printUsageAndExit();
            }
            sscanf(args[cur++].c_str(), "%lf", &out.skelScale);
        } else if(curStr == string("-meshonly") || curStr == string("-mo")) {
            out.stopAtMesh = true;
        } else if(curStr == string("-circlesonly") || curStr == string("-co")) {
            out.stopAfterCircles = true;
        } else if (curStr == string("-nofit")) {
            out.noFit = true;
        } else if(curStr == string("-motion")) {
            if(cur == num) {
                cout << "No motion filename specified; ignoring." << endl;
                continue;
            }
            out.motionname = args[cur++];
        } else if (curStr == string("-algo")) {
            /*  Option to use a different skinning algorithm than the
             *  default LBS. Currently, options are LBS, DQS, and MIX */
            string algo = args[cur++];
            if (algo == string("LBS"))
                out.skinAlgorithm = Mesh::LBS;
            else if (algo == string("DQS"))
                out.skinAlgorithm = Mesh::DQS;
            else if (algo == string("MIX")) {
                /*  Grab the desired blending weight for LBS, i.e
                 *  how much of the result of LBS you want to see */
                if(cur >= num) {
                    cout << "No blending weight given; exiting." << endl;
                    cout << args[cur] << endl;
                    printUsageAndExit();
                }
                out.skinAlgorithm = Mesh::MIX;
                sscanf(args[cur++].c_str(), "%f", &out.blendWeight);
            } else {
                cout << "Unrecognized skinning algorithm" << endl;
                printUsageAndExit();
            }
        } else {
            cout << "Unrecognized option: " << curStr << endl;
            printUsageAndExit();
        }
    }

    return out;
}

void process(const vector<string> &args, MyWindow *w)
{
    int i;
    ArgData a = processArgs(args);

    Debugging::setOutStream(cout);

    Mesh m(a.filename, a.skinAlgorithm, a.blendWeight);
    if(m.vertices.size() == 0) {
        cout << "Error reading file.  Aborting." << endl;
        exit(0);
        return;
    }            
    
    for(i = 0; i < (int)m.vertices.size(); ++i)
        m.vertices[i].pos = a.meshTransform * m.vertices[i].pos;
    m.normalizeBoundingBox();
    m.computeVertexNormals();

    Skeleton given = a.skeleton;
    given.scale(a.skelScale * 0.7);

    if(a.stopAtMesh) { //if early bailout
        w->addMesh(new StaticDisplayMesh(m));
        return;
    }

    PinocchioOutput o;
    if(!a.noFit) { //do everything
        o = autorig(given, m);
    }
    else { //skip the fitting step--assume the skeleton is already correct for the mesh
        TreeType *distanceField = constructDistanceField(m);
        VisTester<TreeType> *tester = new VisTester<TreeType>(distanceField);

        o.embedding = a.skeleton.fGraph().verts;
        for(i = 0; i < (int)o.embedding.size(); ++i)
            o.embedding[i] = m.toAdd + o.embedding[i] * m.scale;

        o.attachment = new Attachment(m, a.skeleton, o.embedding, tester);

        delete tester;
        delete distanceField;
    }

    if(o.embedding.size() == 0) {
        cout << "Error embedding" << endl;
        exit(0);
    }

    if(a.motionname.size() > 0) {
        w->addMesh(new DefMesh(m, given, o.embedding, *(o.attachment),
                    new Motion(a.motionname)));
    }
    else {
        w->addMesh(new StaticDisplayMesh(m));

        for(i = 1; i < (int)o.embedding.size(); ++i)
        {
            w->addLine(LineSegment(o.embedding[i], o.embedding[given.fPrev()[i]], Vector3(.5, .5, 0), 4.));
        }
    }

    //output skeleton embedding
    for(i = 0; i < (int)o.embedding.size(); ++i)
        o.embedding[i] = (o.embedding[i] - m.toAdd) / m.scale;
    ofstream os("skeleton.out");
    for(i = 0; i < (int)o.embedding.size(); ++i) {
        os << i << " " << o.embedding[i][0] << " " << o.embedding[i][1] <<
                   " " << o.embedding[i][2] << " " << a.skeleton.fPrev()[i] << endl;
    }

    //output attachment
    std::ofstream astrm("attachment.out");
    for(i = 0; i < (int)m.vertices.size(); ++i) {
        Vector<double, -1> v = o.attachment->getWeights(i);
        for(int j = 0; j < v.size(); ++j) {
            double d = floor(0.5 + v[j] * 10000.) / 10000.;
            astrm << d << " ";
        }
        astrm << endl;
    }

    delete o.attachment;
}
