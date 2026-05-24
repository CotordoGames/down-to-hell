#include "Input.h"

const bool* Input::keyboard = nullptr;

bool Input::previous[SDL_SCANCODE_COUNT] = {};

void Input::Update(){

    for(int i = 0; i < SDL_SCANCODE_COUNT; i++){
        previous[i] = keyboard ? keyboard[i] : false;
    }

    keyboard = SDL_GetKeyboardState(NULL);

}

bool Input::KeyDown(SDL_Scancode key){
    return keyboard[key];
}

bool Input::KeyPressed(SDL_Scancode key){
    return keyboard[key] && !previous[key];
}

bool Input::KeyReleased(SDL_Scancode key){
    return !keyboard[key] && previous[key];
}