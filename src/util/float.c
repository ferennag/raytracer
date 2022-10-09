#include <math.h>
#include <stdbool.h>
#include "util/float.h"

bool float_eq(float f1, float f2) {
    return fabsf(f1 - f2) < FLOAT_TOLERANCE;
}