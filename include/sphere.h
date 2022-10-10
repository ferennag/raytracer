#ifndef SPHERE_H
#define SPHERE_H

#include "tuple.h"
#include "matrix.h"

typedef struct Sphere {
    Tuple origin;
    Matrix transform;
} Sphere;

Sphere Sphere_create();
void Sphere_set_transformation(Sphere *sphere, const Matrix *transformation);

#endif