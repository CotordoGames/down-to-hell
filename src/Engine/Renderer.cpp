#include "Renderer.h"

SDL_Renderer* Renderer::renderer = nullptr;

bool Renderer::Init(SDL_Window* window){
    renderer = SDL_CreateRenderer(window, NULL);
    return renderer != nullptr;
}

void Renderer::Clear(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::Present(){
    SDL_RenderPresent(renderer);
}

void Renderer::DrawRect(float x, float y, float w, float h, SDL_Color color, bool fill){
    SDL_FRect rect = {x, y, w, h};

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    if(fill){
        SDL_RenderFillRect(renderer, &rect);
    } else{
        SDL_RenderRect(renderer, &rect);
    }
}

void Renderer::ShutDown(){
    if(renderer){
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
}