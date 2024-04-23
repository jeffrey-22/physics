#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>

class Vector {
public:
    double x, y, z;
    explicit Vector(double x=0, double y=0, double z=0) : x(x), y(y), z(z) {}
    Vector operator+(Vector p) const { return Vector(x+p.x, y+p.y, z+p.z); }
    Vector operator-(Vector p) const { return Vector(x-p.x, y-p.y, z-p.z); }
    Vector operator*(double d) const { return Vector(x*d, y*d, z*d); }
    Vector operator/(double d) const { return Vector(x/d, y/d, z/d); }
    double dist2() const { return x*x + y*y + z*z; }
    double dist() const { return std::sqrt(dist2()); }
    friend std::ostream& operator<<(std::ostream& os, Vector p) {
        return os << "(" << p.x << "," << p.y << "," << p.z << ")"; 
    }
    double dot(const Vector& p) const { return x*p.x + y*p.y + z*p.z; }
    Vector cross(const Vector& p) const {
        return Vector(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
    }
    Vector unit() const { return *this/dist(); } //makes d is t ()=1
    //returns unit vector normal to *this and p
    Vector normal(Vector p) const { return cross(p).unit(); }
};

#endif // VECTOR_H