#include <SDL2/SDL.h>
#include <stdbool.h>
#include "util/logger.h"
#include "graphics/graphics.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

void graphics_init(int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        log_fatal(SDL_GetError());
        exit(-1);
    }

    window = SDL_CreateWindow(
        "Raytracer challenge", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    
    if (!window) {
        log_fatal(SDL_GetError());
        exit(-1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        log_fatal(SDL_GetError());
        exit(-1);
    }
}

void graphics_shutdown() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    SDL_Quit();
}

void graphics_run(void (*update_callback)(SDL_Renderer *)) {
    bool should_run = true;

    // Only call it once
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    update_callback(renderer);
    SDL_RenderPresent(renderer);

    while(should_run) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                should_run = false;
                continue;
            }
        }
        SDL_Delay(50);
    }
}