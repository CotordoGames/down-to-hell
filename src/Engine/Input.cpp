#include "Input.h"

uint8_t Input::keyboard[SDL_SCANCODE_COUNT] = {};

bool Input::previous[SDL_SCANCODE_COUNT] = {};

void Input::Update(){

    const auto* state = SDL_GetKeyboardState(NULL);

    for(int i = 0; i < SDL_SCANCODE_COUNT; i++){
        previous[i] = keyboard[i];
        keyboard[i] = state[i];
    }

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