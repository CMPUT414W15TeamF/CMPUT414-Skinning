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

#ifndef QUATINTERFACE_H
#define QUATINTERFACE_H

#include "vector.h"
#include "transfo.hpp"
#include "transform.h"
#include "quat_cu.hpp"
#include "dual_quat_cu.hpp"

Tbx::Dual_quat_cu getQuatFromMat(Transform<> matrix);
    
#endif
