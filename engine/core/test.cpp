#include "engine.cpp"
#include "cuboid_rigidbody.h"

int main() {
    PhysicsEngine engine;
    CuboidRigidBody cuboid;
    engine.addRigidBody(&cuboid);
    engine.simulate(1.0/10, 2.0);
    engine.dumpAllRecordedData();
    return 0;
}