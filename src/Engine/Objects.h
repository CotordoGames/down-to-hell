#pragma once
#include <cmath>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include "Renderer.h"
#include "Mathf.h"

#define OBJECT_SOLID 1 << 0
#define OBJECT_GRAVITY 1<< 1

struct GameObject{
    SDL_Texture* texture;
    vec2 position;
    vec2 velocity;
    vec2 size;
    SDL_FRect collider;
    vec2 colliderOffset;
    uint32_t flags; // OR these together
};

class ObjectManager{
public:
    static GameObject& Add(const GameObject& object);
    static void Update();
    static void Render();
    static bool debug;

private:
    static std::vector<GameObject> Objects; //this is a array of active objects but in C++ so it looks confusing
};