#include "engine.cpp"
#include "cuboid_rigidbody.h"
#include <chrono>

/* Only needed for the sake of this example. */
#include <iostream>
#include <thread>
int main() {
    PhysicsEngine engine;
    std::vector<CuboidRigidBody> v;
    int n = 80;
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    for (int i = 1; i <= n; i++) {
        CuboidRigidBody a(rand() % 10 + 1,1,1,1,Vector(0,0,i),IDENTITY,Vector(0,0,-1),ORIGIN);
        v.push_back(a);
    }
    for (int i = 0; i < n; i++)
        engine.addRigidBody(&v[i]);
    engine.simulate(1.0/30, n * 2);
    // engine.dumpAllRecordedData();
    
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";
    return 0;
}