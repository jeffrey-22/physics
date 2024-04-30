#include "environment.h"
#include "rigidbody.h"

class CollisionDetection {
public:
    static bool bruteForceCheckCollisionForOnePair(RigidBody *a, RigidBody *b, Collision* c = nullptr) {
        return bruteForceCheckFaceVertexCollisionForOnePair(a, b, c) ||
               bruteForceCheckFaceVertexCollisionForOnePair(b, a, c) ||
               bruteForceCheckEdgeEdgeCollisionForOnePair(a, b, c);
    }
    static bool bruteForceCheckFaceVertexCollisionForOnePair(RigidBody *a, RigidBody *b, Collision* c) {
        for (auto face : a->getFaces())
            for (auto vertex : b->getVertices())
                if (checkFaceVertexCollision(a->getLatestState(), b->getLatestState(), face, vertex, a, b, c))
                    return 1;
        return 0;
    }
    static bool bruteForceCheckEdgeEdgeCollisionForOnePair(RigidBody *a, RigidBody *b, Collision* c) {
        for (auto ea : a->getEdges())
            for (auto eb : b->getEdges())
                if (checkEdgeEdgeCollision(a->getLatestState(), b->getLatestState(), ea, eb, a, b, c))
                    return 1;
        return 0;
    }
    static bool checkCollisionIsColliding(Collision *c) {
        Vector va = c->a->computePointVelocity(c->p, c->a->getLatestState());
        Vector vb = c->b->computePointVelocity(c->p, c->b->getLatestState());
        double vab = c->normal.dot(vb - va);
        if (vab > -COLLIDINGTHRESHOLD)
            return false;
        return true;
    }
    static bool checkFaceVertexCollision(RigidBodyState sa, RigidBodyState sb, Face f, Vertex v, RigidBody *a, RigidBody *b, Collision *c) {
        f = toWorldSpaceCoordinates(f, sa);
        v = toWorldSpaceCoordinates(v, sb);
        c = new FaceVertexCollision();
        ((FaceVertexCollision*)c)->face = f;
        ((FaceVertexCollision*)c)->vertex = v;
        c->a = a;
        c->b = b;
        c->normal = computeFaceNormal(f);
        if (c->normal.dot(sb.position - sa.position) < 0)
            c->normal = c->normal * (-1.0);
        c->p = v;
        return checkCollisionIsColliding(c);
    }
    static bool checkEdgeEdgeCollision(RigidBodyState sa, RigidBodyState sb, Edge ea, Edge eb, RigidBody *a, RigidBody *b, Collision* c) {
        ea = toWorldSpaceCoordinates(ea, sa);
        eb = toWorldSpaceCoordinates(eb, sb);
        c = new EdgeEdgeCollision();
        ((EdgeEdgeCollision*)c)->ea = ea;
        ((EdgeEdgeCollision*)c)->eb = eb;
        c->a = a;
        c->b = b;
        c->normal = (ea.second - ea.first).normal(eb.second - ea.first).unit();
        if (c->normal.dot(sb.position - sa.position) < 0)
            c->normal = c->normal * (-1.0);
        c->p = closestPointsOnSegments(ea, eb);
        return checkCollisionIsColliding(c);
    }
};