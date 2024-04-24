#ifndef CUBOID_RIGIDBODY_H
#define CUBOID_RIGIDBODY_H

#include "rigidbody.h"

class CuboidRigidBody : public RigidBody{
public:
    double length, width, height;

    CuboidRigidBody(double mass = 1, double length = 1, double width = 1, double height = 1, Vector initialPosition = ORIGIN, 
    Matrix initialRotation = IDENTITY, Vector initialLinearMomentum = ORIGIN, Vector initialAngularMomentum = ORIGIN)
        : RigidBody(mass, computeBodySpaceInertiaTensor(mass, length, width, height),
            initialPosition, initialRotation, initialLinearMomentum, initialAngularMomentum),
            length(length), width(width), height(height) {
                setConfigurations(0.0, length, width, height);
            }
private:
    static Matrix computeBodySpaceInertiaTensor(double mass, double length, double width, double height) {
        double lengthSqr = length * length, widthSqr = width * width, heightSqr = height * height;
        return Matrix(widthSqr + heightSqr, lengthSqr + heightSqr, lengthSqr + widthSqr) * (mass / 12.0);
    }
};

#endif // CUBOID_RIGIDBODY_H