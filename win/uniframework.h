#ifndef UNIFRAMEWORK_H
#define UNIFRAMEWORK_H

#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>

typedef struct {
    SDL_Window* window;
    int running;
} U_Context;

int U_BeginScreen(U_Context* ctx, const char* title, int width, int height);
void U_Exit(U_Context* ctx);
void U_Shutdown(U_Context* ctx);

#endif