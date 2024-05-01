#ifndef CUBOID_RIGIDBODY_H
#define CUBOID_RIGIDBODY_H

#include "rigidbody.h"

class CuboidRigidBody : public RigidBody{
public:
    double length, width, height;

    CuboidRigidBody(double mass = 1, double length = 1, double width = 1, double height = 1, Vector initialPosition = ORIGIN, 
    Matrix initialRotation = IDENTITY, Vector initialLinearMomentum = ORIGIN, Vector initialAngularMomentum = ORIGIN)
        : RigidBody(mass, computeBodySpaceInertiaTensor(mass, length, width, height),
            initialPosition, initialRotation, initialLinearMomentum, initialAngularMomentum),
            length(length), width(width), height(height) {
                setConfigurations(0.0, length, width, height);
                auto A = Vector(length / 2, width / 2, -height / 2),
                B =  Vector(length / 2, width / 2, height / 2),
                C =  Vector(length / 2, -width / 2, -height / 2),
                D =  Vector(length / 2, -width / 2, height / 2),
                E =  Vector(-length / 2, width / 2, -height / 2),
                F =  Vector(-length / 2, width / 2, height / 2),
                G =  Vector(-length / 2, -width / 2, -height / 2),
                H =  Vector(-length / 2, -width / 2, height / 2);
                vertices.push_back(A);
                vertices.push_back(B);
                vertices.push_back(C);
                vertices.push_back(D);
                vertices.push_back(E);
                vertices.push_back(F);
                vertices.push_back(G);
                vertices.push_back(H);
                edges.push_back(std::make_pair(A, B));
                edges.push_back(std::make_pair(C, D));
                edges.push_back(std::make_pair(E, F));
                edges.push_back(std::make_pair(G, H));
                edges.push_back(std::make_pair(A, C));
                edges.push_back(std::make_pair(C, G));
                edges.push_back(std::make_pair(G, E));
                edges.push_back(std::make_pair(E, A));
                edges.push_back(std::make_pair(B, D));
                edges.push_back(std::make_pair(D, H));
                edges.push_back(std::make_pair(H, F));
                edges.push_back(std::make_pair(F, B));
                faces.push_back(std::tie(A, B, C));
                faces.push_back(std::tie(A, B, E));
                faces.push_back(std::tie(G, H, E));
                faces.push_back(std::tie(G, H, C));
                faces.push_back(std::tie(A, C, E));
                faces.push_back(std::tie(B, D, F));
                forceAndTorque.force = Vector(0, 0, -1) * mass * 9.8;
            }
private:
    static Matrix computeBodySpaceInertiaTensor(double mass, double length, double width, double height) {
        double lengthSqr = length * length, widthSqr = width * width, heightSqr = height * height;
        return Matrix(widthSqr + heightSqr, lengthSqr + heightSqr, lengthSqr + widthSqr) * (mass / 12.0);
    }
};

#endif // CUBOID_RIGIDBODY_H