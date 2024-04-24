#include "engine.cpp"
#include "cuboid_rigidbody.h"
#include <Eigen/Dense>

int main() {
    PhysicsEngine engine;
    CuboidRigidBody cuboid;
    engine.addRigidBody(cuboid);
    engine.dumpAllRecordedData();
    
    Eigen::Matrix3d matrix;
    matrix << 1, 2, 3,
              4, 5, 6,
              7, 8, 9;
    return 0;
}