#include <stdlib.h>
#include "intersection.h"
#include "data/list.h"

Intersection *Intersection_create(float value, const void *object) {
    Intersection *result = malloc(sizeof(Intersection));
    result->value = value;
    result->object = object;
    return result;
}

Intersections *Intersections_create() {
    List *list = List_empty(NULL);

    Intersections *result = malloc(sizeof(Intersections));
    result->list = list;
    result->cnt = 0;
    return result;
}
void Intersections_destroy(Intersections **intersections) {
    List_destroy((*intersections)->list);
    free(*intersections);
    *intersections = NULL;
}

void Intersections_add(Intersections *intersections, float value, const void *object) {
    Intersection *intersection = Intersection_create(value, object);
    List_append(intersections->list, intersection);
    intersections->cnt += 1;
}