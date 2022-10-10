#ifndef SPHERE_H
#define SPHERE_H

#include "tuple.h"

typedef struct Sphere {
    Tuple origin;
} Sphere;

Sphere Sphere_create();

#endif