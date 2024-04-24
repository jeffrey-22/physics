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
private:

};