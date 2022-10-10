#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "data/list.h"

typedef struct Intersection {
    float value;
    const void *object;
} Intersection;

typedef struct Intersections {
    List *list;
    unsigned int cnt;
} Intersections;

Intersection *Intersection_create(float value, const void *object);
Intersections *Intersections_create();
void Intersections_destroy(Intersections *intersections);
void Intersections_add(Intersections *intersections, float value, const void *object);

#endif