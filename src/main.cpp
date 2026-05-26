#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_main.h>
#include "Engine/Engine.h"
#include <cmath>


int main(int argc, char* argv[]){
    
    //initialize SDL3 and make sure it doesnt kill your program
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("SDL failed to initialize! err: %s", SDL_GetError());
        return 1;
    }

    //create the window
    SDL_Window* window = SDL_CreateWindow("Down To Hell -- v A0.00", 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN);

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
                SDL_SetRenderLogicalPresentation(Renderer::renderer, 320, 240, SDL_LOGICAL_PRESENTATION_LETTERBOX);
            }
        }
        Uint64 start = SDL_GetTicks();

        Input::Update();

        //do object stuff

        ObjectManager::Update();


        Renderer::Clear();

        //draw stuff here
        ObjectManager::Render();

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