#include "environment.h"
#include "collision_resolution.cpp"

class PhysicsEngine {
public:
    std::vector<RigidBody*> bodies;
    double currentTime = 0.0;
    void addRigidBody(RigidBody* body) {
        bodies.push_back(body);
    }
    void dumpAllRecordedData() {
        for (auto body : bodies) {
            auto configurations = body->getConfigurations();
            for (auto value : configurations)
                std::cout << value << " ";
            auto states = body->getStates();
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
    void advanceByTimeFrameUnderConstantForce(double dt) {
        for (auto body : bodies) {
            auto states = body->getStates();
            auto [time, state] = states.back();
            auto stateDerivative = body->computeDerivative(state, body->getForceAndTorque());
            stateDerivative.angularMomentum = stateDerivative.angularMomentum * dt + state.angularMomentum;
            stateDerivative.linearMomentum = stateDerivative.linearMomentum * dt + state.linearMomentum;
            stateDerivative.position = stateDerivative.position * dt + state.position;
            stateDerivative.rotation = stateDerivative.rotation * dt + state.rotation;
            stateDerivative.position = stateDerivative.position.unit() * 20.0;
            body->addState(std::make_pair(time + dt, stateDerivative));
        }
        currentTime += dt;
    }
    void rollBack() {
        for (auto body : bodies) {
            body->rollBack();
        }
        auto [time, state] = bodies.back()->getStates().back();
        currentTime = time;
    }
    int bruteForceCheckCollision(Collision* c = nullptr) {
        int n = bodies.size();
        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = 1; k <= 200; k++)
                    cnt+=i & j & k;
        return 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (CollisionDetection::bruteForceCheckCollisionForOnePair(bodies[i], bodies[j], c))
                    return 1;
        return 0;
    }
    double findFirstCollisionTime(double dt) {
        auto left = currentTime;
        auto right = currentTime + dt;
        auto eps = 1e-5;
        while (right - left > eps) {
            auto middle = (left + right) / 2.0;
            advanceByTimeFrameUnderConstantForce(middle - left);
            if (bruteForceCheckCollision())
                right = middle;
            else
                left = middle;
            rollBack();
        }
        return right;
    }
    Collision* advanceToFirstCollision(double dt) {
        Collision *c;
        double time = findFirstCollisionTime(dt);
        advanceByTimeFrameUnderConstantForce(time);
        bruteForceCheckCollision(c);
        return c;
    }
    void initializeForce() {

    }
    void simulate(double dt, double totalTime) {
        initializeForce();
        while(currentTime < totalTime) {
            advanceByTimeFrameUnderConstantForce(dt);
            if (bruteForceCheckCollision()) {
                rollBack();
                auto c = advanceToFirstCollision(dt);
                CollisionResolution::resolveCollision(c);
            }
            std::cout << 1;
        }
    }
private:

};