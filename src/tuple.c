#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "tuple.h"
#include "util/float.h"

Tuple Tuple_create(float x, float y, float z, float w) {
    Tuple tuple = {x, y, z, w};
    return tuple;
}

Tuple Tuple_point(float x, float y, float z) {
    return Tuple_create(x, y, z, 1.0);
}

Tuple Tuple_vector(float x, float y, float z) {
    return Tuple_create(x, y, z, 0.0);
}

Tuple Tuple_color(float red, float green, float blue) {
    return Tuple_vector(red, green, blue);
}

void Tuple_as_array(Tuple t, float *array) {
    array[0] = t.x;
    array[1] = t.y;
    array[2] = t.z;
    array[3] = t.w;
}

void Tuple_print(Tuple tuple) {
    printf("(%2.2f, %2.2f, %2.2f, %2.2f)\n", tuple.x, tuple.y, tuple.z, tuple.w);
}

bool Tuple_eq(const Tuple *t1, const Tuple *t2) {
    return float_eq(t1->x, t2->x) && float_eq(t1->y, t2->y) && float_eq(t1->z, t2->z) && float_eq(t1->w, t2->w);
}

Tuple Tuple_add(Tuple a, Tuple b) {
    return Tuple_create(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    );
}

Tuple Tuple_sub(Tuple a, Tuple b) {
    return Tuple_create(
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.w - b.w
    );
}

float Tuple_dot(Tuple a, Tuple b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Tuple Tuple_cross(Tuple a, Tuple b) {
    return Tuple_vector(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

Tuple Tuple_negate(Tuple a) {
    return Tuple_create(
        -a.x,
        -a.y,
        -a.z,
        -a.w
    );
}

Tuple Tuple_smul(Tuple a, float scalar) {
    return Tuple_create(
        a.x * scalar,
        a.y * scalar,
        a.z * scalar,
        a.w * scalar
    );
}

Tuple Tuple_sdiv(Tuple a, float scalar) {
    return Tuple_create(
        a.x / scalar,
        a.y / scalar,
        a.z / scalar,
        a.w / scalar
    );
}

Tuple Tuple_hadamard(Tuple a, Tuple b) {
    return Tuple_color(
        a.x * b.x,
        a.y * b.y,
        a.z * b.z
    );
}

float Tuple_magnitude(Tuple a) {
    return sqrtf(
        pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2) + pow(a.w, 2)
    );
}

Tuple Tuple_normalize(Tuple a) {
    float m = Tuple_magnitude(a);
    return Tuple_create(
        a.x / m,
        a.y / m,
        a.z / m,
        a.w / m
    );
}