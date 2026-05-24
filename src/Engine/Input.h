#pragma once

#include <SDL3/SDL.h>

class Input{
public:
    static void Update();

    static bool KeyDown(SDL_Scancode key);
    static bool KeyPressed(SDL_Scancode key);
    static bool KeyReleased(SDL_Scancode key);

private:
    static const bool* keyboard;
    static bool previous[SDL_SCANCODE_COUNT];
};