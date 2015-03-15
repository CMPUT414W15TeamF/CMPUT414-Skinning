/*
 * =====================================================================================
 *
 *       Filename:  QuatInterface.cpp
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  03/14/2015 07:01:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "quatinterface.h"
#include "vector.h"

using namespace Tbx;

Dual_quat_cu getQuatFromMat(Transform<> matrix) {
    Mat3 mat3;
    Vector<double, 3> trans;
    Vec3 transVec3;
    Quaternion<double> quat;
    Dual_quat_cu dualQuat;
    Transfo transfo;
    int x = 0, y = 1, z = 2;

    // Get rotation, convert to Vec3
    trans = matrix.getTrans();
    transVec3 = Vec3(trans[0], trans[1], trans[2]);

    // Get rotation axis and angle
    quat = matrix.getRot();
    double angle = quat.getAngle();
    Vector<double, 3> axis = quat.getAxis();
    Vec3 axisVec3 = Vec3(axis[0], axis[1], axis[2]);

    /*
    // Create rotation quaternion from axis and angle
    double sin_a = sin(angle / 2);
    double cos_a = cos(angle / 2);
    double qx = axis[x] * sin_a;
    double qy = axis[y] * sin_a;
    double qz = axis[z] * sin_a;
    double qw = cos_a;
    Quat_cu rotquat = Quat_cu(qw, qx, qy, qz);
    */
    Quat_cu rotquat = Quat_cu(axisVec3, (float) angle);
    
    /*  
    // create rotation matrix from angle and axis
    rads = angle;
    Real c = cos(rads);
    Real s = sin(rads);
    
    mat3 = Mat3(
            c + axis[x] * axis[x] * 
            (1-c), axis[x] * axis[y] * (1 - c) - axis[z] * s,
            axis[x] * axis[z] * (1-c) + axis[y] * s,
            axis[y] * axis[x] * (1-c) + axis[z] * s,
            c + axis[y] * axis[y] * (1-c),
            axis[y] * axis[z] * (1-c) - axis[x] * s,
            axis[z] * axis[x] * (1-c) - axis[y] * s,
            axis[z] * axis[y] * (1-c) + axis[x] * s,
            c + axis[z] * axis[z] * (1-c)
            );

    // convert to Transfo matrix
    transfo = Transfo(mat3, transVec3);
    */

    // convert matrix to quaternion
    dualQuat = Dual_quat_cu(rotquat, transVec3);
    return dualQuat;
}
    

