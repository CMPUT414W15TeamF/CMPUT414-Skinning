/*
 * =====================================================================================
 *
 *       Filename:  quatinterface.h
 *
 *    Description: Header file for quatinterface.cpp. See the source file for details
 *                on different functions defined here.
 *
 *        Version:  1.0
 *        Created:  03/14/2015 07:01:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Group F, CMPUT414 Winter 2015
 *
 * =====================================================================================
 */

#ifndef QUATINTERFACE_H
#define QUATINTERFACE_H

#include "vector.h"
#include "transfo.hpp"
#include "transform.h"
#include "quat_cu.hpp"
#include "dual_quat_cu.hpp"

Tbx::Dual_quat_cu getQuatFromMat(Transform<> matrix);
Vector3 transformPoint(Vector3 vpos, Tbx::Dual_quat_cu &dquat_blend);

#endif
