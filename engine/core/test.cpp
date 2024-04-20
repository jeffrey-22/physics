#include "collision_detection.cpp"

int main() {
    Sphere A(Vector(0, 0, 0), Vector(1, 0, 0), 1, 1, 1);
    Sphere B(Vector(3, 0, 0), Vector(-1, 0, 0), 1, 1, 1);
    for (int i = 0; i < 100; i++) {
        A.updatePosition(0.01);
        B.updatePosition(0.01);
        if (A.isColliding(B))
            A.resolveSphereCollision(B);
        if (B.isColliding(A))
            B.resolveSphereCollision(A);
        std::cout << A.position << " " << B.position << std::endl;
    }
}
