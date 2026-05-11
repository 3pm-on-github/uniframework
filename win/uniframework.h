#ifndef UNIFRAMEWORK_H
#define UNIFRAMEWORK_H

#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int running;
} U_Context;

typedef struct {
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;
} U_RGBA;

int U_BeginScreen(U_Context* ctx, const char* title, int width, int height);
void U_ClearScreen(U_Context* ctx);
void U_PresentScreen(U_Context* ctx);
void U_DrawRect(U_Context* ctx, int x, int y, int w, int h, U_RGBA color);
void U_DrawPixel(U_Context* ctx, int x, int y, U_RGBA color);
void U_Exit(U_Context* ctx);
void U_Shutdown(U_Context* ctx);
void U_Delay(unsigned int ms);

#endif