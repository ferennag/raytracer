#include <stdio.h>
#include <stdlib.h>
#include "graphics/graphics.h"

int main(int argc, char *argv[]) {
    graphics_init(1024, 768);
    graphics_run();
    graphics_shutdown();
    return 0;
}
