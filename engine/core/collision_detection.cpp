#include "../../geometry/matrix.h"

class Sphere {
public:
    Vector position;
    Vector velocity;
    double radius, mass, invMass, currentTime;
    std::vector<std::tuple<double, Vector>> recorder;

    Sphere(const Vector position, const Vector velocity, double radius, double mass, double invMass) : 
        position(position), velocity(velocity), radius(radius), mass(mass), invMass(invMass), recorder() {}

    // Function to check if two spheres are colliding
    bool isColliding(const Sphere& other) const {
        double distance2 = (position - other.position).dist2();
        double minDistance = radius + other.radius;
        double minDistance2 = minDistance * minDistance;
        return distance2 < minDistance2;
        
    }

    // Function to resolve collision between two spheres
    void resolveSphereCollision(Sphere& other) {
        Vector normalDirection = other.position - position;
        double factor = -normalDirection.dot(velocity);
        factor *= 2.0;
        velocity = velocity + normalDirection * factor;
    }

    Vector computeForce() {
        return Vector(0, 0, -mass * 9.8);
    }

    void updatePosition(double dt) {
        Vector force = computeForce();
        Vector acceleration = force * invMass;
        velocity = velocity + acceleration * dt;
        position = position + velocity * dt;
        currentTime += dt;
    }

    void setCurrentTime(double newCurrentTime) {
        currentTime = newCurrentTime;
    }

    void recordPosition() {
        recorder.push_back({currentTime, position});
    }

    void printRecorder() {
        
    }
};
