#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "../geometry/matrix.h"

const Vector ORIGIN(0, 0, 0);
const Matrix IDENTITY(1, 1, 1);

typedef std::tuple<Vector, Vector, Vector> Face;
typedef std::pair<Vector, Vector> Edge;

#endif // ENVIRONMENT_H