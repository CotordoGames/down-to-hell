#pragma once
#include <SDL3/SDL.h>

class Renderer{
public:
    static bool Init(SDL_Window* window);
    static void Clear();
    static void Present();
    static void ShutDown();

    //draw calls
    static void DrawRect(float x, float y, float w, float h, SDL_Color color, bool fill);

    //renderer
    static SDL_Renderer* renderer;
};