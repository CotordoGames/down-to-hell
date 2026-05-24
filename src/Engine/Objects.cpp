#include "Objects.h"
#include "Renderer.h"

std::vector<GameObject> ObjectManager::Objects;

GameObject& ObjectManager::Add(const GameObject& object){
    Objects.push_back(object);

    return Objects.back();
}

void ObjectManager::Update(){
    for(GameObject& obj : Objects){

        obj.x += obj.vx;
        obj.y += obj.vy;

        obj.collider.x = obj.x;
        obj.collider.y = obj.y;
    }
}

void ObjectManager::Render(){
    for(GameObject& obj : Objects){

        Renderer::DrawTexture(
            obj.texture,
            std::round(obj.x),
            std::round(obj.y),
            obj.w,
            obj.h
        );
    }
}