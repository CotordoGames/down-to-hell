#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_main.h>
#include "Engine/Input.h"
#include "Engine/Renderer.h"

int x = 0;
int y = 0;
int vx = 0;
int vy = 0;

int main(int argc, char* argv[]){
    
    //initialize SDL3 and make sure it doesnt kill your program
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("SDL failed to initialize! err: %s", SDL_GetError());
        return 1;
    }

    //create the window
    SDL_Window* window = SDL_CreateWindow("Down To Hell -- v A0.00", 640, 480, SDL_WINDOW_RESIZABLE);

    //make sure SDL actually made the window
    if(!window){
        SDL_Log("SDL failed to create the window! err: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    Renderer::Init(window);

    SDL_Log("Hello, World!");

    //loop
    bool running = true;
    SDL_Event event;
    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                running = false;
            } else if(event.type == SDL_EVENT_WINDOW_RESIZED){
                SDL_SetRenderLogicalPresentation(Renderer::renderer, 320, 180, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
            }
        }
        Uint64 start = SDL_GetTicks();

        Input::Update();

        vx = (Input::KeyDown(SDL_SCANCODE_RIGHT) - Input::KeyDown(SDL_SCANCODE_LEFT)) * 4;
        vy = (Input::KeyDown(SDL_SCANCODE_DOWN) - Input::KeyDown(SDL_SCANCODE_UP)) * 4;

        x += vx;
        y += vy;

        Renderer::Clear();

        //draw stuff here
        Renderer::DrawRect(x, y, 16, 16, (SDL_Color){255, 0, 0, 255}, true);

        Renderer::Present();

        Uint64 frameTime = SDL_GetTicks() - start;

        if(frameTime < 15){
            SDL_Delay(15 - frameTime);
        }
    }

    //clean up your toys
    Renderer::ShutDown();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}