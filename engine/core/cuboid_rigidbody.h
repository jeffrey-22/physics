#ifndef CUBOID_RIGIDBODY_H
#define CUBOID_RIGIDBODY_H

#include "rigidbody.h"

class CuboidRigidBody : RigidBody{
public:
    double length, width, height;

private:
    void computeBodySpaceInertiaTensor() {
        double lengthSqr = length * length, widthSqr = width * width, heightSqr = height * height;
        bodySpaceInertiaTensor = Matrix(widthSqr + heightSqr, lengthSqr + heightSqr, lengthSqr + widthSqr) * (mass / 12.0);
    }
};

#endif // CUBOID_RIGIDBODY_H