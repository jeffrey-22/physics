#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

const std::size_t MATRIX_SIZE = 3;

class Matrix {
public:
    std::vector<double> data;
    Matrix() : data(MATRIX_SIZE * MATRIX_SIZE, 0.0) {}

    Matrix(double diag1, double diag2, double diag3) 
        : data({diag1, 0.0, 0.0,
                0.0, diag2, 0.0,
                0.0, 0.0, diag3}) {}

    const double& operator()(std::size_t row, std::size_t col) const {
        return data[row * MATRIX_SIZE + col];
    }

    Vector operator*(Vector rhs) const {
        return Vector(
            rhs.x * data[0] + rhs.y * data[1] + rhs.z * data[2],
            rhs.x * data[3] + rhs.y * data[4] + rhs.z * data[5],
            rhs.x * data[6] + rhs.y * data[7] + rhs.z * data[8]
        );
    }

    static Matrix star(const Vector& v) {
        return Matrix(
            0,    -v.z,  v.y,
            v.z,   0,   -v.x,
           -v.y,  v.x,   0
        );
    }

    Matrix inverse() const {
        if (data.size() != MATRIX_SIZE * MATRIX_SIZE) {
            throw std::invalid_argument("Matrix must be 3x3 to find its inverse.");
        }

        double det = data[0] * (data[4] * data[8] - data[5] * data[7]) -
                     data[1] * (data[3] * data[8] - data[5] * data[6]) +
                     data[2] * (data[3] * data[7] - data[4] * data[6]);

        if (det == 0.0) {
            throw std::invalid_argument("Matrix does not have an inverse.");
        }

        double invDet = 1.0 / det;

        Matrix adjugate(
            data[4]*data[8] - data[5]*data[7], data[2]*data[7] - data[1]*data[8], data[1]*data[5] - data[2]*data[4],
            data[5]*data[6] - data[3]*data[8], data[0]*data[8] - data[2]*data[6], data[2]*data[3] - data[0]*data[5],
            data[3]*data[7] - data[4]*data[6], data[1]*data[6] - data[0]*data[7], data[0]*data[4] - data[1]*data[3]
        );

        Matrix invMatrix(
            adjugate(0, 0) * invDet, adjugate(0, 1) * invDet, adjugate(0, 2) * invDet,
            adjugate(1, 0) * invDet, adjugate(1, 1) * invDet, adjugate(1, 2) * invDet,
            adjugate(2, 0) * invDet, adjugate(2, 1) * invDet, adjugate(2, 2) * invDet
        );

        return invMatrix;
    }

    Matrix operator*(const Matrix& rhs) const {
        if (data.size() != MATRIX_SIZE * MATRIX_SIZE || rhs.data.size() != MATRIX_SIZE * MATRIX_SIZE) {
            throw std::invalid_argument("Matrices must be 3x3 for multiplication.");
        }

        Matrix result;

        for (std::size_t i = 0; i < MATRIX_SIZE; ++i) {
            for (std::size_t j = 0; j < MATRIX_SIZE; ++j) {
                result.data[i * MATRIX_SIZE + j] = 
                    data[i * MATRIX_SIZE] * rhs.data[j] + 
                    data[i * MATRIX_SIZE + 1] * rhs.data[MATRIX_SIZE + j] + 
                    data[i * MATRIX_SIZE + 2] * rhs.data[2 * MATRIX_SIZE + j];
            }
        }

        return result;
    }

    Matrix operator+(const Matrix& rhs) const {
        if (data.size() != MATRIX_SIZE * MATRIX_SIZE || rhs.data.size() != MATRIX_SIZE * MATRIX_SIZE) {
            throw std::invalid_argument("Matrices must be 3x3 for addition.");
        }

        Matrix result;

        for (std::size_t i = 0; i < MATRIX_SIZE; ++i) {
            for (std::size_t j = 0; j < MATRIX_SIZE; ++j) {
                result.data[i * MATRIX_SIZE + j] = data[i * MATRIX_SIZE + j] + rhs.data[i * MATRIX_SIZE + j];
            }
        }

        return result;
    }

    Matrix operator-(const Matrix& rhs) const {
        if (data.size() != MATRIX_SIZE * MATRIX_SIZE || rhs.data.size() != MATRIX_SIZE * MATRIX_SIZE) {
            throw std::invalid_argument("Matrices must be 3x3 for subtraction.");
        }

        Matrix result;

        for (std::size_t i = 0; i < MATRIX_SIZE; ++i) {
            for (std::size_t j = 0; j < MATRIX_SIZE; ++j) {
                result.data[i * MATRIX_SIZE + j] = data[i * MATRIX_SIZE + j] - rhs.data[i * MATRIX_SIZE + j];
            }
        }

        return result;
    }

    Matrix operator*(double scalar) const {
        Matrix result;

        for (std::size_t i = 0; i < MATRIX_SIZE; ++i) {
            for (std::size_t j = 0; j < MATRIX_SIZE; ++j) {
                result.data[i * MATRIX_SIZE + j] = data[i * MATRIX_SIZE + j] * scalar;
            }
        }

        return result;
    }

    friend Matrix operator*(double scalar, const Matrix& matrix) {
        return matrix * scalar;
    }

    Matrix& operator+=(const Matrix& rhs) {
        if (data.size() != MATRIX_SIZE * MATRIX_SIZE || rhs.data.size() != MATRIX_SIZE * MATRIX_SIZE) {
            throw std::invalid_argument("Matrices must be 3x3 for addition.");
        }

        for (std::size_t i = 0; i < MATRIX_SIZE; ++i) {
            for (std::size_t j = 0; j < MATRIX_SIZE; ++j) {
                data[i * MATRIX_SIZE + j] += rhs.data[i * MATRIX_SIZE + j];
            }
        }

        return *this;
    }

    Matrix& operator*=(double scalar) {
        for (std::size_t i = 0; i < MATRIX_SIZE; ++i) {
            for (std::size_t j = 0; j < MATRIX_SIZE; ++j) {
                data[i * MATRIX_SIZE + j] *= scalar;
            }
        }

        return *this;
    }

private:
    Matrix(double a, double b, double c, 
           double d, double e, double f, 
           double g, double h, double i) 
        : data({a, b, c, d, e, f, g, h, i}) {}
};

#endif // MATRIX_H