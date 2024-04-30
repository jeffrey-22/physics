#include "environment.h"
#include "collision_detection.cpp"

class CollisionResolution {
public:
    static void resolveCollision(Collision* c, double coefficientOfResititution = DEFAULTCOEFFICIENT) {
        Vector va = c->a->computePointVelocity(c->p, c->a->getLatestState());
        Vector vb = c->b->computePointVelocity(c->p, c->b->getLatestState());
        Vector n = c->normal;
        Vector ra = c->p - c->a->getLatestState().position;
        Vector rb = c->p - c->b->getLatestState().position;
        double vab = n.dot(vb - va);
        double nu = -(1 + coefficientOfResititution) * vab;
        double t1 = 1 / c->a->getMass();
        double t2 = 1 / c->b->getMass();
        double t3 = n.dot((c->a->getInverseInertia(c->a->getLatestState()) * ra.cross(n)).cross(ra));
        double t4 = n.dot((c->b->getInverseInertia(c->b->getLatestState()) * rb.cross(n)).cross(rb));
        double j = nu / (t1 + t2 + t3 + t4);
        Vector f = n * j;
        c->a->getLatestState().linearMomentum = c->a->getLatestState().linearMomentum + f;
        c->b->getLatestState().linearMomentum = c->b->getLatestState().linearMomentum - f;
        c->a->getLatestState().angularMomentum = c->a->getLatestState().angularMomentum + ra.cross(f);
        c->b->getLatestState().angularMomentum = c->b->getLatestState().angularMomentum - rb.cross(f);
    }
};