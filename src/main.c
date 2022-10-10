#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "graphics/graphics.h"
#include "ray.h"
#include "sphere.h"
#include "intersection.h"

const int PIXELS = 600;

static Sphere sphere;

void update_callback(SDL_Renderer *renderer) {
    Tuple ray_origin = Tuple_point(0, 0, -5);
    float wall_z = 10;
    float wall_size = 7;
    float pixel_size = wall_size / PIXELS;
    float half = wall_size / 2;

    // The sphere's color
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

    for(int y = 0; y < PIXELS; y++) {
        float world_y = half - pixel_size * y;

        for (int x = 0; x < PIXELS; x++) {
            float world_x = -half + pixel_size * x;
            Tuple target = Tuple_point(world_x, world_y, wall_z);
            Tuple target_vector = Tuple_normalize(Tuple_sub(target, ray_origin));
            Ray ray = Ray_create(ray_origin, target_vector);
            Intersections *is = Ray_intersect(&ray, &sphere);

            if(is->cnt > 0) {
                SDL_RenderDrawPoint(renderer, x, y);   
            }

            Intersections_destroy(&is);
        }
    }
}

int main(int argc, char *argv[]) {
    sphere = Sphere_create();
    // Matrix transform = Matrix_scaling(1, .5, 1);
    // Sphere_set_transformation(&sphere, &transform);

    graphics_init(PIXELS, PIXELS);
    graphics_run(update_callback);
    graphics_shutdown();
    return 0;
}
