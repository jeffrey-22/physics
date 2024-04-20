#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../../geometry/matrix.h"
#include <fstream>

class RigidBodyState {
public:
    Vector position, linearMomentum, angularMomentum;
    Matrix rotation;
};

class RigidBodyAuxilaries {
public:
    Vector linearVelocity, angularVelocity;
    Matrix inertia;
    double invMass;
};

class RigidBody {
public:
    double mass;
    Matrix bodySpaceInertiaTensor;
    
    RigidBodyState state, derivativeState;

    RigidBodyAuxilaries auxilaries;

    Vector force, torque;
    
private:
    void computeAuxilaryQuantities() {
        auxilaries.invMass = 1.0 / mass;
        auxilaries.linearVelocity = state.linearMomentum * auxilaries.invMass;
        auxilaries.inertia = state.rotation * bodySpaceInertiaTensor * state.rotation.inverse();
        auxilaries.angularVelocity = auxilaries.inertia.inverse() * state.angularMomentum;
    }
    void computeDerivative() {
        derivativeState.position = auxilaries.linearVelocity;
        derivativeState.rotation = Matrix::star(auxilaries.angularVelocity) * state.rotation;
        derivativeState.angularMomentum = force;
        derivativeState.linearMomentum = torque;
    }
};

#endif // RIGIDBODY_H