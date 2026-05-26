#include "Objects.h"
#include "Renderer.h"
#include "Input.h"

std::vector<GameObject> ObjectManager::Objects;
bool ObjectManager::debug = false;

GameObject& ObjectManager::Add(const GameObject& object){
    Objects.push_back(object);

    return Objects.back();
}

void ObjectManager::Update(){
    for(GameObject& obj : Objects){

        obj.position.x += obj.velocity.x;
        obj.position.y += obj.velocity.y;

        obj.collider.x = obj.position.x + obj.colliderOffset.x;
        obj.collider.y = obj.position.y + obj.colliderOffset.y;
    }
    if(Input::KeyPressed(SDL_SCANCODE_F1)){
        debug = !debug;
    }
}

void ObjectManager::Render(){
    for(GameObject& obj : Objects){

        Renderer::DrawTexture(
            obj.texture,
            obj.position.x,
            obj.position.y,
            obj.size.x,
            obj.size.y
        );
        if(debug){
            Renderer::DrawRect(obj.collider.x, obj.collider.y, obj.collider.w, obj.collider.h, (SDL_Color){0, 255, 0, 255}, false);
        }
    }
}