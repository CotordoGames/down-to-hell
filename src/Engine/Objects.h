#pragma once
#include <cmath>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include "Renderer.h"

struct GameObject{
    SDL_Texture* texture;
    float x, y;
    float vx, vy;
    float w, h;
    SDL_FRect collider;
    uint32_t flags; // OR these together
};

class ObjectManager{
public:
    static GameObject& Add(const GameObject& object);
    static void Update();
    static void Render();

private:
    static std::vector<GameObject> Objects; //this is a array of active objects but in C++ so it looks confusing
};