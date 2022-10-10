#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "tuple.h"

typedef struct canvas {
    Tuple **pixels;
} canvas;

void graphics_init();
void graphics_shutdown();
void graphics_run();

#endif