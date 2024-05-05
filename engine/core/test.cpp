#include "engine.cpp"
#include "cuboid_rigidbody.h"

int main() {
    PhysicsEngine engine;
    CuboidRigidBody a(1,1,1,1,Vector(0,0,0),IDENTITY,Vector(1,0,0),ORIGIN); a.forceAndTorque.force = ORIGIN;
    CuboidRigidBody b(1,1,1,1,Vector(2,0,0),IDENTITY,Vector(-1,0,0),ORIGIN); b.forceAndTorque.force = ORIGIN;
    engine.addRigidBody(&a);
    engine.addRigidBody(&b);
    engine.simulate(1.0/10, 2.0);
    engine.dumpAllRecordedData();
    return 0;
}