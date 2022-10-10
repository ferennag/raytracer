#ifndef RAY_H
#define RAY_H

#include "tuple.h"
#include "sphere.h"
#include "intersection.h"

typedef struct Ray {
    Tuple origin;
    Tuple direction;
} Ray;

Ray Ray_create(Tuple origin, Tuple direction);
Tuple Ray_position(const Ray *ray, float t);
Intersections *Ray_intersect(const Ray *ray, const Sphere *sphere);

#endif