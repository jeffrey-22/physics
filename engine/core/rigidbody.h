#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "environment.h"

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

class RigidBodyForceAndTorque {
public:
    Vector force, torque;
};

class RigidBody {
public:
    double mass;
    Matrix bodySpaceInertiaTensor;
    
    RigidBodyState state, derivativeState;

    RigidBodyAuxilaries auxilaries;
    
    RigidBody(double mass, const Matrix& bodySpaceInertiaTensor, Vector initialPosition = ORIGIN, 
    Matrix initialRotation = IDENTITY, Vector initialLinearMomentum = ORIGIN, Vector initialAngularMomentum = ORIGIN)
        : mass(mass), bodySpaceInertiaTensor(bodySpaceInertiaTensor) {

        }
private:
    RigidBodyAuxilaries computeAuxilaryQuantities(RigidBodyState state) {
        RigidBodyAuxilaries auxilaries;
        auxilaries.invMass = 1.0 / mass;
        auxilaries.linearVelocity = state.linearMomentum * auxilaries.invMass;
        auxilaries.inertia = state.rotation * bodySpaceInertiaTensor * state.rotation.inverse();
        auxilaries.angularVelocity = auxilaries.inertia.inverse() * state.angularMomentum;
        return auxilaries;
    }
    RigidBodyState computeDerivative(RigidBodyState state, RigidBodyForceAndTorque forceAndTorque) {
        RigidBodyAuxilaries auxilaries;
        auxilaries = computeAuxilaryQuantities(state);
        RigidBodyState derivativeState;
        derivativeState.position = auxilaries.linearVelocity;
        derivativeState.rotation = Matrix::star(auxilaries.angularVelocity) * state.rotation;
        derivativeState.angularMomentum = forceAndTorque.force;
        derivativeState.linearMomentum = forceAndTorque.torque;
        return derivativeState;
    }
};

#endif // RIGIDBODY_H