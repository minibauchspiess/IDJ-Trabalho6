#include "include/Face.h"
#include <iostream>

using namespace std;

#define START_HP 30

Face::Face(GameObject& associated) : Component(associated)
{
    hitpoints = START_HP;
}

void Face::Damage(int damage){
    hitpoints = hitpoints - damage;

    //When dies, delete "enemy"
    if (hitpoints <= 0){

        associated.RequestDelete();

        Sound* sound = (Sound*) associated.GetComponent("sound").get();
        if (sound != nullptr){
            sound->Play(1);
        }

    }
}

void Face::Update(float dt){
    InputManager& input = InputManager::GetInstance();

    //If the left mouse button was pressed uppon the face, damage it
    if(input.MousePress(LMOUSE) && associated.box.IsIn( Vec2(input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y) ) ){
        Damage(std::rand() % 10 + 10);
    }
}

void Face::Render(){

}

bool Face::Is(string type){
    return !type.compare("face");
}
