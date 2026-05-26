#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_main.h>
#include "Engine/Engine.h"
#include <cmath>

GameObject initPlayer;
GameObject initSolid;

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

    //--player init--//
    //initialize objects before first frame is drawn
    initPlayer.texture = IMG_LoadTexture(Renderer::renderer, "assets/sprites/objects/player.png");
    SDL_SetTextureScaleMode(initPlayer.texture, SDL_SCALEMODE_NEAREST);

    initPlayer.position = {1, 1};

    initPlayer.size = {8, 8};

    initPlayer.velocity = {0, 0};

    initPlayer.flags = OBJECT_SOLID;

    initPlayer.collider = {0, 0, 8, 8};

    initPlayer.colliderOffset = {0, 0};

    GameObject& player = ObjectManager::Add(initPlayer);
    //--player init--//

    //--solid init--//
    //initialize objects before first frame is drawn
    initSolid.texture = IMG_LoadTexture(Renderer::renderer, "assets/sprites/objects/player.png");
    SDL_SetTextureScaleMode(initSolid.texture, SDL_SCALEMODE_NEAREST);

    initSolid.position = {160, 120};

    initSolid.size = {8, 8};

    initSolid.velocity = {0, 0};

    initSolid.flags = OBJECT_SOLID;

    initSolid.collider = {0, 0, 8, 8};

    initSolid.colliderOffset = {0, 0};

    GameObject& solid = ObjectManager::Add(initSolid);
    //--init solid--//
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

        player.velocity.x = std::lerp(player.velocity.x, (Input::KeyDown(SDL_SCANCODE_RIGHT) - Input::KeyDown(SDL_SCANCODE_LEFT)) * 4, 0.1);
        player.velocity.y = std::lerp(player.velocity.y, (Input::KeyDown(SDL_SCANCODE_DOWN) - Input::KeyDown(SDL_SCANCODE_UP)) * 4, 0.1);

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