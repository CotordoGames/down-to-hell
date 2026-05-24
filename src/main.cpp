#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_main.h>

int x = 0;

int y = 0;

int main(int argc, char* argv[]){

    if(argc < 3){
        SDL_Log("usage: ./game x y");
        return 1;
    }

    //initialize SDL3 and make sure it doesnt kill your program
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("SDL failed to initialize! err: %s", SDL_GetError());
        return 1;
    }
    x = std::stoi(argv[1]);
    y = std::stoi(argv[2]);

    //create the window
    SDL_Window* window = SDL_CreateWindow("Down To Hell -- v A0.00", 640, 480, 0);

    //make sure SDL actually made thew window
    if(!window){
        SDL_Log("SDL failed to create the window! err: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if(!renderer){
        SDL_Log("SDL failed to initialize the renderer! err: %s", SDL_GetError());
        return 1;
    }

    std::cout << "hello, world!" << std::endl;

    SDL_FRect rect = {(float)x, (float)y, 32, 32};

    //loop
    bool running = true;
    SDL_Event event;
    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 127, 127, 255, 255);
        SDL_RenderClear(renderer);

        //draw stuff here
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    //clean up your toys
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}