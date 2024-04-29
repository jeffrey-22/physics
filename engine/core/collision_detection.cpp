#include "rigidbody.h"

class FaceVertexCollision : public Collision {
    Face face;
    Vector vertex;
};
class EdgeEdgeCollision : public Collision {
    Edge ea, eb;
};
class Collision {
    RigidBody *a, *b;
    Vector normal;
};