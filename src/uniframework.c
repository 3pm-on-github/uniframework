#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "uniframework.h"

// SDL wrapper functions
// Coded by: 3pm
void U_ClearScreen(U_Context* ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctx->renderer);
}

void U_Delay(unsigned int ms) {
    SDL_Delay(ms);
}

void U_PresentScreen(U_Context* ctx) {
    SDL_RenderPresent(ctx->renderer);
}

void U_SetFont(U_Context* ctx, const char* font_path, int font_size) {
    ctx->font = TTF_OpenFont(font_path, font_size);
    if (!ctx->font) {
        printf("Font loading failed: %s\n", TTF_GetError());
    }
}

// Initializing stuff
// Coded by: 3pm
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

    ctx->renderer = SDL_CreateRenderer(ctx->window, -1, SDL_RENDERER_ACCELERATED);
    if (!ctx->renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(ctx->window);
        return 0;
    }
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ctx->running = 1;
    return 1;
}

// Drawing functions
// Coded by: 3pm
void U_DrawRect(U_Context* ctx, int x, int y, int w, int h, U_RGBA color) {
    SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(ctx->renderer, &rect);
}

void U_DrawPixel(U_Context* ctx, int x, int y, U_RGBA color) {
    SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(ctx->renderer, x, y);
}


void U_DrawText(U_Context* ctx, int x, int y, const char* text, U_RGBA color) {
    if (!ctx->font) return;
    SDL_Color sdl_color = { color.r, color.g, color.b, color.a };
    SDL_Surface* surface = TTF_RenderText_Blended(ctx->font, text, sdl_color);
    if (!surface) {
        TTF_CloseFont(ctx->font);
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ctx->renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        TTF_CloseFont(ctx->font);
        return;
    }

    SDL_Rect dst = { x, y, 0, 0 };
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ctx->renderer, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(ctx->font);
}

// Exit stuff
// Coded by: 3pm
void U_Exit(U_Context* ctx) {
    SDL_Quit();
    TTF_CloseFont(ctx->font);
    TTF_Quit();
    if (ctx->renderer) {
        SDL_DestroyRenderer(ctx->renderer);
        ctx->renderer = NULL;
    }
    if (ctx->window) {
        SDL_DestroyWindow(ctx->window);
        ctx->window = NULL;
    }
    if (ctx->font) {
        TTF_CloseFont(ctx->font);
        ctx->font = NULL;
    }
    ctx->running = 0;
}