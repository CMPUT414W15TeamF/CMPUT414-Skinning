# CMPUT414-Skinning

This is the group project of Skinning topic in the course of CMPUT414

## Pinocchio Citing

The readme and license information for Pinocchio are available in the 
Pinocchio directory.

Authors of the code: Ilya Baran and Jovan Popovic, from their paper
"Automatic Rigging and Animation of 3D Characters" SIGGRAPH 2007.

## Dual Quaternion Library Citing

The code used for creating, manipulating, and transformting with dual 
quaternions is available in the following files:
* dual_quat_cu.hpp
* mat3.hpp
* point3.hpp
* quat_cu.hpp
* transfo.hpp
* vec3.hpp 

Author of code: Rodolphe Vaillant-David

## Our Changes / Contributions

We have modified the following files in order to combine pinocchio with
the dual quaternion skinning library:
* attachment.cpp

We created the following file to help with the interfacing between the 
different classes from each library:
* quatinterface.hpp
* quatinterface.cpp

## References

We used the following websites and papers to help us and as guides to 
integrating dual quaternions into pinocchio.
* http://rodolphe-vaillant.fr/?e=29
* Kavan, Ladislav, et al. "Skinning with dual quaternions." Proceedings of the
  2007 symposium on Interactive 3D graphics and games. ACM, 2007.
* Baran, Ilya, and Jovan Popović. "Automatic rigging and animation of 3d
  characters." ACM Transactions on Graphics (TOG). Vol. 26. No. 3. ACM, 2007. 

Eigen library and Armadillo library are added for matrix manipulations

Eigen Library: http://eigen.tuxfamily.org/index.php?title=Main_Page

Armrdillo Library: http://arma.sourceforge.net/
