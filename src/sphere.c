#include "sphere.h"
#include "tuple.h"

Sphere Sphere_create() {
    Sphere sphere = {.origin = Tuple_point(0, 0, 0)};
    return sphere;
}