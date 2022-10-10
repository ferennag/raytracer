#include <assert.h>
#include <stdlib.h>
#include "sphere.h"
#include "tuple.h"
#include "matrix.h"

Sphere Sphere_create() {
    Sphere sphere = {.origin = Tuple_point(0, 0, 0), .transform = Matrix_identity4()};
    return sphere;
}

void Sphere_set_transformation(Sphere *sphere, const Matrix *transformation) {
    assert(sphere != NULL && transformation != NULL);
    sphere->transform = *transformation;
}