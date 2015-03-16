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

    // Get translation, convert to Vec3
    trans = matrix.getTrans();
    transVec3 = Vec3(trans[0], trans[1], trans[2]);

    // Get rotation axis and angle
    quat = matrix.getRot();
    double angle = quat.getAngle();
    Vector<double, 3> axis = quat.getAxis();
    Vec3 axisVec3 = Vec3(axis[0], axis[1], axis[2]);

    // Create rotation quaternion from axis and angle
    Quat_cu rotquat = Quat_cu(axisVec3, (float) angle);
    
    // convert matrix to quaternion
    dualQuat = Dual_quat_cu(rotquat, transVec3);
    return dualQuat;
}
    
Vector3 transformPoint(Vector3 vpos, Dual_quat_cu &dquat_blend) {
    Point3 restPos = Point3(vpos[0], vpos[1], vpos[2]);
    Point3 newPos = dquat_blend.transform(restPos);
    return Vector3(newPos.x, newPos.y, newPos.z);
}
