#ifndef TUPLE_H_
#define TUPLE_H_

#include <stdbool.h>

typedef struct Tuple {
    float x;
    float y;
    float z;
    float w;
} Tuple;

Tuple Tuple_create(float x, float y, float z, float w);
Tuple Tuple_point(float x, float y, float z);
bool Tuple_ispoint(const Tuple *t);
Tuple Tuple_vector(float x, float y, float z);
bool Tuple_isvector(const Tuple *t);
Tuple Tuple_color(float red, float green, float blue);
void Tuple_as_array(Tuple t, float *array);
bool Tuple_eq(const Tuple *t1, const Tuple *t2);
void Tuple_print(Tuple tuple);

Tuple Tuple_add(Tuple a, Tuple b);
Tuple Tuple_sub(Tuple a, Tuple b);
float Tuple_dot(Tuple a, Tuple b);
Tuple Tuple_cross(Tuple a, Tuple b);
Tuple Tuple_negate(Tuple a);
Tuple Tuple_smul(Tuple a, float scalar);
Tuple Tuple_sdiv(Tuple a, float scalar);
Tuple Tuple_hadamard(Tuple a, Tuple b);

float Tuple_magnitude(Tuple a);
Tuple Tuple_normalize(Tuple a);

#endif