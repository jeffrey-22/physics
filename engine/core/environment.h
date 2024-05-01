#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "../geometry/matrix.h"
#include <tuple>
#include <assert.h>

const Vector ORIGIN(0, 0, 0);
const Matrix IDENTITY(1, 1, 1);

typedef std::tuple<Vector, Vector, Vector> Face;
typedef std::pair<Vector, Vector> Edge;
typedef Vector Vertex;

struct RigidBodyState {
public:
    Vector position, linearMomentum, angularMomentum;
    Matrix rotation;
};

struct RigidBodyAuxilaries {
public:
    Vector linearVelocity, angularVelocity;
    Matrix inertia;
    double invMass;
};

struct RigidBodyForceAndTorque {
public:
    Vector force, torque;
};

static Vector toWorldSpaceCoordinates(Vector bodySpaceCoordinates, RigidBodyState& state) {
    return state.position + state.rotation * bodySpaceCoordinates;
}
static Edge toWorldSpaceCoordinates(Edge bodySpaceCoordinates, RigidBodyState& state) {
    return std::make_pair(toWorldSpaceCoordinates(bodySpaceCoordinates.first, state), 
    toWorldSpaceCoordinates(bodySpaceCoordinates.second, state));
}
static Face toWorldSpaceCoordinates(Face bodySpaceCoordinates, RigidBodyState& state) {
    auto [a, b, c] = bodySpaceCoordinates;
    return std::make_tuple(toWorldSpaceCoordinates(a, state), 
    toWorldSpaceCoordinates(b, state),
    toWorldSpaceCoordinates(c, state));
}
static Vector toBodySpaceCoordinates(Vector worldSpaceCoordinates, RigidBodyState& state) {
    return state.rotation.inverse() * (worldSpaceCoordinates - state.position);
}
static Vector computeFaceNormal(const Face& face) {
    Vector p1, p2, p3;
    std::tie(p1, p2, p3) = face;

    Vector edge1 = p2 - p1;
    Vector edge2 = p3 - p1;

    Vector normal = edge1.cross(edge2);

    return normal.unit();
}
const double COLLIDINGTHRESHOLD = 1e-3;
const double DEFAULTCOEFFICIENT = 0.5;
static Vector closestPointsOnSegments(const Edge& segmentA, const Edge& segmentB) {
    Vector p1 = segmentA.first;
    Vector q1 = segmentA.second;
    Vector p2 = segmentB.first;
    Vector q2 = segmentB.second;

    Vector d1 = q1 - p1;
    Vector d2 = q2 - p2;

    double len1 = d1.dist2();
    double len2 = d2.dist();

    double dot12 = d1.dot(d2);

    double t1, t2;

    Vector n = d1.cross(d2);
    t1 = (p2 - p1).cross(d2).dot(n) / n.dist2();

    t1 = std::max(0.0, std::min(1.0, t1));

    Vector closestA = p1 + d1 * t1;

    return closestA;
}

#endif // ENVIRONMENT_H