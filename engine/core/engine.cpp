#include "environment.h"
#include "collision_detection.cpp"
#include "collision_resolution.cpp"

class PhysicsEngine {
public:
    std::vector<RigidBody> bodies;
    void addRigidBody(RigidBody body) {
        bodies.emplace_back(body);
    }
    void dumpAllRecordedData() {
        for (auto body : bodies) {
            auto configurations = body.getConfigurations();
            for (auto value : configurations)
                std::cout << value << " ";
            auto states = body.getStates();
            std::cout << states.size() << " " << std::endl;
            for (auto [time, state] : states) {
                std::cout << time << " ";
                Vector position = state.position;
                Matrix rotation = state.rotation;
                std::cout << position.x << " " << position.y << " " << position.z << " ";
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        std::cout << rotation.data[i * 3 + j] << " ";
                std::cout << std::endl;
            }
        }
    }
    void advanceByTimeFrameUnderConstantForce(double dt, RigidBodyForceAndTorque forceAndTorque) {
        for (auto body : bodies) {
            auto states = body.getStates();
            auto [time, state] = states.back();
            auto stateDerivative = body.computeDerivative(state, forceAndTorque);
            stateDerivative.angularMomentum = stateDerivative.angularMomentum * dt + state.angularMomentum;
            stateDerivative.linearMomentum = stateDerivative.linearMomentum * dt + state.linearMomentum;
            stateDerivative.position = stateDerivative.position * dt + state.position;
            stateDerivative.rotation = stateDerivative.rotation * dt + state.rotation;
            states.emplace_back(std::make_pair(time + dt, stateDerivative));
        }
    }
private:

};