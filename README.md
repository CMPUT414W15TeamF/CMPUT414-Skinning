# CMPUT414-Skinning

This is group F's project on Skinning for the course of CMPUT414 Winter 2015.

## Table of Content
* [Pinocchio Code](#pinocchio)
* [Dual Quaternion Skinning Library](#dqs)
* [Our Changes / Contributions ](#changes)
* [How to Compile](#compile)
* [How to Run](#run)
* [References](#references)


## <a name="pinocchio"></a> Pinocchio Code 

Pinocchio prototype was written by Ilya Baran and Jovan Popovic. Details for
the implementation and algorithms used can be found in their paper paper
"Automatic Rigging and Animation of 3D Characters" SIGGRAPH 2007.

The readme and license information for Pinocchio are available in the 
Pinocchio directory.

## <a name="dqs"></a> Dual Quaternion Skinning Library

The Dual Quaternion Skinning Library was created by Rodolphe Vaillant-David.

The code provides the functionality necessary for creating, manipulating, and
transformting with dual quaternions. The files encompassing this library are:
* dual_quat_cu.hpp
* mat3.hpp
* point3.hpp
* quat_cu.hpp
* transfo.hpp
* vec3.hpp 


## <a name="changes"></a>Our Changes / Contributions

The main goal of our project was to use the existing prototype Pinocchio and 
to change the skinning implementation of LBS it uses to improve the results.
At first we tried changing the original LBS algorithm a bit, but the results
were quite terrible. 

Our next step was to implement an altogether different algorithm for skinning.
We decided on dual quaternion skinning (DQS) because it was the easiest in terms of
changing a program that currently uses LBS to use dual quaternions. We found
a dual quaternion skinning library by Vaillant-David (mentioned above) which
already had the functions implemented to accomplish the creation and 
manipulation of dual quaternions (eg. multiplying them together), and also
a function to transform a point by a transformation defined by a dual 
quaternion. Our main challenge was just integrating the two approaches since
they both used their own different data structures.

We were able to succesfully integrate this two different codes so that 
Pinocchio was skinning by using dual quaternions instead of transformation
matrices (LBS). 

We then also decided to see if by blending the results of LBS and DQS the
visual results could be improved (since DQS is said to have the problem of
the "bulging" artifcat). We did a few more modifications in order to choose
if we wanted to run the pinocchio using LBS, DQS, or a mix of both.

All in all, below is a list of all the files we modified in order for our 
project:
* Pinocchio/attachment.cpp
* Pinocchio/attachment.h
* Pinocchio/mesh.h
* Pinocchio/mesh.cpp
* Pinocchio/Makefile
* DemoUI/processor.cpp
* DemoUI/processor.h
* DemoUI/Makefile
* Makefile

We created the following file to help with the interfacing between the 
different classes from each library:
* quatinterface.hpp
* quatinterface.cpp

## <a name="compile"></a> How to Compile

Before compiling, make sure you have the following libraries installed:
* FLTK library (on linux, run `sudo apt-get install libfltk1.1-dev`)
* OpenGL (on linux, run `sudo apt-get install freeglut3-dev`)

To compile, cd into the uppermost Pinocchio directory
`cd CMPUT414-Skinning/Pinocchio/`

Then, run `make`.

## <a name="run"></a>How to Run

In order to run Pinocchio for the purposes of this project, first make sure you add the path to libpinocchio.so to your
LD_LIBRARY_PATH variable in your .bashrc. By default, it should be in the folder `CMPUT414-Skinning/Pinocchio/Pinocchio`.

Then, to actually run the program, there are a few options. Below is the general command to use:
`/path/to/DemoUI path/to/obj/file -motion path/to/mocap/file [-algo <LBS|DQS|MIX> <blend_weight>`

* /path/to/DemoUI : the path to the DemoUI executable file (by default should be in `CMPUT414-Skinning/Pinocchio/DemoUI`)
* /path/to/obj/file : the path to the object file you wish to rig / skin
* -motion : specifies you want to use a motion capture file
* path/to/mocap/file : path to the motion capture file you want to use. Note that you can only use the motion capture files that come with Pinocchio (found under `CMPUT414-Skinning/Pinocchio/DemoUI/data`)
* -algo : used to specify a specific skinning algorithm you want to use. If this is not specified, by default LBS will be used.
* LBS|DQS|MIX : the 3 different skinning algorithms to choose from. LBS = linear blend skinning, DQS = dual quaternion skinning, MIX = mixed result from both LBS and DQS.
* <blend_weight> : only needed if chosen skinning algorithm is MIX. This blend weight specifies how much of the LBS result you want blended in. By default, if not specified, .5 will be used so the final result will be 50% from LBS and 50% from DQS. A blend weight of 0.0 would mean you are only using the result from DQS, while a blend weight of 1.0 means the result will be solely based on LBS.

Below is an example of running the program on command line, assuming you have not changed the directory structure of this repo and that you are in the uppermost Pinocchio folder:
`./DemoUI/DemoUI ../meshes/Model1.obj -motion DemoUI/data/wakeUpSequence2.txt -algo MIX 0.2`

## <a name="references"></a>References

We used the following websites and papers to help us and as guides to 
integrating dual quaternions into pinocchio.
* http://rodolphe-vaillant.fr/?e=29
* Kavan, Ladislav, et al. "Skinning with dual quaternions." Proceedings of the
  2007 symposium on Interactive 3D graphics and games. ACM, 2007.
* Baran, Ilya, and Jovan Popović. "Automatic rigging and animation of 3d
  characters." ACM Transactions on Graphics (TOG). Vol. 26. No. 3. ACM, 2007. 
