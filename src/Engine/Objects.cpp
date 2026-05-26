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

        //store Ys old position, move the object, and update the X collider with it
        float oldX = obj.position.x;
        obj.position.x += obj.velocity.x;
        obj.collider.x = obj.position.x + obj.colliderOffset.x;

        //we are not blocked by default
        bool BlockedX = false;

        //resolve X collision
        for(GameObject& col : Objects){
            //dont do this if the object is just colliding with itself
            if(&obj == &col) continue;

            //dont collide if the object isnt solid
            if(!(col.flags & OBJECT_SOLID)) continue;

            //are we colliding?
            bool collidingX = (
                obj.collider.x < col.collider.x + col.collider.w && obj.collider.x + obj.collider.w > col.collider.x &&
                obj.collider.y < col.collider.y + col.collider.h && obj.collider.y + obj.collider.h > col.collider.y
            );

            //if yes, then tell the object.
            if(collidingX){
                BlockedX = true;
                break;
            }
        }

        //resolve X
        if(BlockedX){
            obj.position.x = oldX;
            obj.velocity.x = 0;
            obj.collider.x = obj.position.x + obj.colliderOffset.x;
        }

        //same idea for Y
        float oldY = obj.position.y;
        obj.position.y += obj.velocity.y;
        obj.collider.y = obj.position.y + obj.colliderOffset.y;

        //not blocked by default
        bool BlockedY = false;

        //resolve Y collision
        for(GameObject& col : Objects){
            //dont do this if the object is just colliding with itself
            if(&obj == &col) continue;

            //dont collide if the object isnt solid
            if(!(col.flags & OBJECT_SOLID)) continue;

            //are we colliding?
            bool collidingY = (
                obj.collider.x < col.collider.x + col.collider.w && obj.collider.x + obj.collider.w > col.collider.x &&
                obj.collider.y < col.collider.y + col.collider.h && obj.collider.y + obj.collider.h > col.collider.y
            );

            //if yes, then tell the object.
            if(collidingY){
                BlockedY = true;
                break;
            }
        }

        //resolve Y
        if(BlockedY){
            obj.position.y = oldY;
            obj.velocity.y = 0;
            obj.collider.y = obj.position.y + obj.colliderOffset.y;
        }


        /*if(obj.flags & OBJECT_SOLID){
            for(GameObject& col : Objects){
                if(col.flags & OBJECT_SOLID){
                    bool colliding = (
                        obj.collider.x < col.collider.x + col.collider.w && obj.collider.x + obj.collider.w > col.collider.x &&
                        obj.collider.y < col.collider.y + col.collider.h && obj.collider.y + obj.collider.h > col.collider.y
                    );
                }
            }
        }*/
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