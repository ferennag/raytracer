#include <stdio.h>
#include <stdlib.h>
#include "tuple.h"
#include "matrix.h"
#include "data/list.h"
#include "data/hashmap.h"

typedef struct projectile {
    Tuple position;
    Tuple velocity;
} projectile;

typedef struct env {
    Tuple gravity;
    Tuple wind;
} env;

projectile tick(env e, projectile p) {
    Tuple position = Tuple_add(p.position, p.velocity);
    Tuple velocity = Tuple_add(Tuple_add(p.velocity, e.gravity), e.wind);
    return (projectile) { position, velocity };
}

void print_item(void *data) {
    if(data != NULL) {
        printf("%d -> ", *(int *)data);
    } else {
        printf("END \n");
    }
}

int *num(int num) {
    int *result = (int *)malloc(sizeof(int));
    *result = num;
    return result;
}

int main(int argc, char *argv[]) {
    projectile p = {Tuple_point(0.0, 1.0, 0.0), Tuple_normalize(Tuple_vector(1.0, 1.0, 0.0))};
    env e = {Tuple_vector(0.0, -0.1, 0.0), Tuple_vector(-0.01, 0.0, 0.0)};

    int i = 1;
    while(p.position.y >=  0) {
        printf("%d: ", i++);
        Tuple_print(p.position);
        p = tick(e, p);
    }

    Matrix m1 = Matrix_zeroes4();
    Matrix m2 = Matrix_zeroes3();
    printf("%d\n", Matrix_eq(&m1, &m2));

    Matrix m3 = Matrix_identity4();
    Matrix m4 = Matrix_submatrix(&m3, 0, 0);
    Matrix_print(&m4);

    float testMatrix[] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
    Matrix m5 = Matrix_create(testMatrix, 3);
    Matrix_print(&m5);
    float cofactor00 = Matrix_cofactor(&m5, 0, 0);
    float cofactor10 = Matrix_cofactor(&m5, 1, 0);
    printf("cofactor = %f\n", cofactor00);
    printf("cofactor = %f\n", cofactor10);


    float det3Matrix[] = {1, 2, 6, -5, 8, -4, 2, 6, 4};
    Matrix m6 = Matrix_create(det3Matrix, 3);
    float det3 = Matrix_det(&m6);
    printf("det3 = %f\n\n", det3);

    float det4Matrix[] = {-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9};
    Matrix m7 = Matrix_create(det4Matrix, 4);
    // printf("cofactor = %f\n", cofactor);
    float det4 = Matrix_det(&m7);
    printf("det4 = %f\n", det4);

    float iMatrix[] = {-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4};
    Matrix m8 = Matrix_create(iMatrix, 4);
    float m8det = Matrix_det(&m8);
    printf("det8 = %f\n", m8det);
    Matrix inverse = Matrix_inverse(&m8);
    Matrix_print(&inverse);

    List *list = List_empty(NULL);
    List_append(list, num(10));
    List_append(list, num(11));
    List_append(list, num(12));
    List_insert(list, num(1));
    List_insert(list, num(0));
    List_forEach(list, print_item);

    printf("size = %d\n", List_size(list));
    printf("value = %d\n", *((int *)List_at(list, 4)));

    List_destroy(list);

    HashMap *map = HashMap_empty(NULL);
    HashMap_put(map, "first", num(10));
    HashMap_put(map, "second", num(20));

    printf("first = %d\n", *((int *)HashMap_get(map, "first")));
    printf("second = %d\n", *((int *)HashMap_get(map, "second")));
    printf("third = %p\n", HashMap_get(map, "third"));
    HashMap_destroy(map);
}
