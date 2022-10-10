#include <assert.h>
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
    assert(intersections != NULL);
    List_destroy((*intersections)->list);
    free(*intersections);
    *intersections = NULL;
}

void Intersections_add(Intersections *intersections, float value, const void *object) {
    assert(intersections != NULL);
    Intersection *intersection = Intersection_create(value, object);

    Node *it = intersections->list->head->next;

    bool added = false;
    while (it != intersections->list->tail) {
        Intersection *current = (Intersection *) it->data;
        if(intersection->value < current->value) {
            List_insert_before(intersections->list, it, intersection);
            added = true;
            break;
        }
        it = it->next;
    }

    if (!added) {
        List_append(intersections->list, intersection);
    }

    intersections->cnt += 1;
}

Intersection *Intersections_at(Intersections *is, unsigned int idx) {
    if (idx > is->cnt - 1) {
        return NULL;
    }

    return (Intersection *) List_at(is->list, idx);
} 

bool nonNegativeIntersection(const void *object) {
    Intersection *i = (Intersection *)object;
    return i->value > 0;
}

Intersection *Intersections_hit(Intersections *is) {
    assert(is != NULL);

    Node *it = List_findFirstBy(is->list, nonNegativeIntersection);
    return it != NULL ? (Intersection *) it->data : NULL;
}