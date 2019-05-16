#include "include/Camera.h"
#include "include/Game.h"

GameObject* Camera::focus;
Vec2 Camera::speed;
Vec2 Camera::pos = Vec2(0,0);

Camera::Camera()
{
    pos = Vec2(0,0);
}

void Camera::Follow(GameObject *newFocus){
    focus = newFocus;
    speed = Vec2(0,0);
}

void Camera::Unfollow(){
    focus = nullptr;
}

void Camera::Update(float dt){
    InputManager &input = InputManager::GetInstance();
    //If camera has a focus, follow it
    if(focus != nullptr){
        pos.x = (focus->box.x + focus->box.w/2) - Game::GetInstance().GetWindowWidth()/2;
        pos.y = (focus->box.y + focus->box.h/2) - Game::GetInstance().GetWindowHeight()/2;
    }
    //Otherwise, follow input commands
    else{
        int resultX = (int)(input.IsKeyDown(RARROW) - input.IsKeyDown(LARROW)),   //Resulting direction for X axis, given the input
            resultY = (int)(input.IsKeyDown(DARROW) - input.IsKeyDown(UARROW));        //Resulting direction for Y axis, given the input

        speed = Vec2( resultX * SPEED,      //Velociy in the X axis
                    resultY * SPEED );      //Velociy in the Y axis
        pos = Vec2::Add(pos, Vec2( resultX*SPEED*dt, resultY*SPEED*dt ));
    }
}
