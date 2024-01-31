#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../../geometry/matrix.h"

class RigidBody {
public:
    Vector linearVelocity, angularVelocity;
    Vector position;
    Matrix rotation;
    Vector linearAcceleration, angularAcceleration;
    double mass, invMass;
    
};

#endif // RIGIDBODY_H