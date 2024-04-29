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
    std::vector<double> configurations;
    std::vector<Vector> vertices;
    std::vector<Edge> edges;
    std::vector<Face> faces;

    RigidBodyForceAndTorque forceAndTorque;
    
    std::vector<std::pair<double, RigidBodyState>> states;
    
    RigidBody(double mass, const Matrix& bodySpaceInertiaTensor, Vector initialPosition = ORIGIN, 
    Matrix initialRotation = IDENTITY, Vector initialLinearMomentum = ORIGIN, Vector initialAngularMomentum = ORIGIN)
        : mass(mass), bodySpaceInertiaTensor(bodySpaceInertiaTensor) {
            RigidBodyState initialState;
            initialState.position = initialPosition;
            initialState.rotation = initialRotation;
            initialState.linearMomentum = initialLinearMomentum;
            initialState.angularMomentum = initialAngularMomentum;
            states = {std::make_pair(0, initialState)};
        }
    template<typename... Args>
    void setConfigurations(Args... args) {
        configurations = {args...};
    }
    const std::vector<double>& getConfigurations() const {
        return configurations;
    }
    RigidBodyForceAndTorque getForceAndTorque() const {
        return forceAndTorque;
    }
    const std::vector<std::pair<double, RigidBodyState>>& getStates() const {
        return states;
    }
    void appendState(double time, RigidBodyState newState) {
        states.emplace_back(std::make_pair(time, newState));
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
private:
    RigidBodyAuxilaries computeAuxilaryQuantities(RigidBodyState state) {
        RigidBodyAuxilaries auxilaries;
        auxilaries.invMass = 1.0 / mass;
        auxilaries.linearVelocity = state.linearMomentum * auxilaries.invMass;
        auxilaries.inertia = state.rotation * bodySpaceInertiaTensor * state.rotation.inverse();
        auxilaries.angularVelocity = auxilaries.inertia.inverse() * state.angularMomentum;
        return auxilaries;
    }
};

#endif // RIGIDBODY_H