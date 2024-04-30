#include "engine.cpp"
#include "cuboid_rigidbody.h"

int main() {
    PhysicsEngine engine;
    CuboidRigidBody cuboid;
    engine.addRigidBody(cuboid);
    engine.dumpAllRecordedData();
    return 0;
}