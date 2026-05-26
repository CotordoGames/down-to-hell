#include "Renderer.h"
#include <cmath>

SDL_Renderer* Renderer::renderer = nullptr;

bool Renderer::Init(SDL_Window* window){
    renderer = SDL_CreateRenderer(window, NULL);
    if(!renderer){
        return false;
    }
    SDL_SetRenderLogicalPresentation(
        renderer,
        320,
        240,
        SDL_LOGICAL_PRESENTATION_LETTERBOX
    );

    SDL_SetRenderVSync(renderer, 1);
    
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
    SDL_FRect rect = {std::round(x), std::round(y), w, h};

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    if(fill){
        SDL_RenderFillRect(renderer, &rect);
    } else{
        SDL_RenderRect(renderer, &rect);
    }
}

void Renderer::DrawTexture(SDL_Texture* tex, float x, float y, float w, float h){
    if(!tex){
        return;
    }
    SDL_FRect src;
    src.x = 0;
    src.y = 0;
    
    float tw, th;
    SDL_GetTextureSize(tex, &tw, &th);

    src.w = tw;
    src.h = th;

    SDL_FRect dst;
    dst.x = std::round(x);
    dst.y = std::round(y);
    dst.w = w;
    dst.h = h;
    SDL_RenderTexture(renderer, tex, &src, &dst);
}

void Renderer::ShutDown(){
    if(renderer){
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
}