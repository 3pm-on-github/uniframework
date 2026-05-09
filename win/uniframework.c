#include <SDL2/SDL.h>
#include <stdio.h>
#include "uniframework.h"

int U_BeginScreen(U_Context* ctx, const char* title, int width, int height) {
    ctx->window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        0
    );

    if (!ctx->window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return 0;
    }

    ctx->running = 1;
    return 1;
}

void U_Exit(U_Context* ctx) {
    ctx->running = 0;
}

void U_Shutdown(U_Context* ctx) {
    if (ctx->window) {
        SDL_DestroyWindow(ctx->window);
        ctx->window = NULL;
    }
}