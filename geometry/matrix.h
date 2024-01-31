#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

class Matrix {
public:
    Matrix() : data(9, double()) {}

    const double& operator()(std::size_t row, std::size_t col) const {
        return data[row * 3 + col];
    }
    Vector operator*(Vector rhs) const {
        return Vector(rhs.x * data[0] + rhs.y * data[1] + rhs.z * data[2], 
                      rhs.x * data[3] + rhs.y * data[4] + rhs.z * data[5], 
                      rhs.x * data[6] + rhs.y * data[7] + rhs.z * data[8]);
    }
private:
    std::vector<double> data;
};

#endif // MATRIX_H