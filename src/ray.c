#include <assert.h>
#include <math.h>
#include "ray.h"
#include "tuple.h"
#include "sphere.h"
#include "intersection.h"

Ray Ray_create(Tuple origin, Tuple direction) {
    assert(Tuple_ispoint(&origin) && Tuple_isvector(&direction));

    Ray ray = {.origin = origin, .direction = direction};
    return ray;
}

Tuple Ray_position(const Ray *ray, float t) {
    Tuple scaled_dir = Tuple_smul(ray->direction, t);
    return Tuple_add(ray->origin, scaled_dir);
}

Intersections *Ray_intersect(const Ray *ray, const Sphere *sphere) {
    Tuple sphere_to_ray = Tuple_sub(ray->origin, sphere->origin);
    
    float a = Tuple_dot(ray->direction, ray->direction);
    float b = 2 * Tuple_dot(ray->direction, sphere_to_ray);
    float c = Tuple_dot(sphere_to_ray, sphere_to_ray) - 1;

    float discriminant = powf(b, 2) - 4 * a * c;

    Intersections *result = Intersections_create();

    if (discriminant < 0) {
        // The ray is missing the sphere
        return result;
    }

    float i1 = (-b - sqrtf(discriminant)) / (2 * a);
    float i2 = (-b + sqrtf(discriminant)) / (2 * a);
    
    Intersections_add(result, i1, sphere);
    Intersections_add(result, i2, sphere);

    return result;
}