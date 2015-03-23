# CMPUT414-Skinning

This is group F's project on Skinning for the course of CMPUT414 Winter 2015.

## Table of Content
* [anchor](#anchor)
* [Pinocchio Code](##Pinocchio Code)
* [Dual Quaternion Skinning Library](##Dual Quaternion Skinning Library)
* [Our Changes / Contributions ](##Our Changes / Contributions)
* [How to Compile](##How to Compile)
* [How to Run](##How to Run)


## Pinocchio Code 

Pinocchio prototype was written by Ilya Baran and Jovan Popovic. Details for
the implementation and algorithms used can be found in their paper paper
"Automatic Rigging and Animation of 3D Characters" SIGGRAPH 2007.

The readme and license information for Pinocchio are available in the 
Pinocchio directory.

#anchor
## Dual Quaternion Skinning Library

The Dual Quaternion Skinning Library was created by Rodolphe Vaillant-David.

The code provides the functionality necessary for creating, manipulating, and
transformting with dual quaternions. The files encompassing this library are:
* dual_quat_cu.hpp
* mat3.hpp
* point3.hpp
* quat_cu.hpp
* transfo.hpp
* vec3.hpp 


## Our Changes / Contributions

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

## How to Compile

## How to Run

## References

We used the following websites and papers to help us and as guides to 
integrating dual quaternions into pinocchio.
* http://rodolphe-vaillant.fr/?e=29
* Kavan, Ladislav, et al. "Skinning with dual quaternions." Proceedings of the
  2007 symposium on Interactive 3D graphics and games. ACM, 2007.
* Baran, Ilya, and Jovan Popović. "Automatic rigging and animation of 3d
  characters." ACM Transactions on Graphics (TOG). Vol. 26. No. 3. ACM, 2007. 
