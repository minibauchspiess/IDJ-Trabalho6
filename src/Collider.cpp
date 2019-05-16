#include "include/Collider.h"
//#define DEBUG         //For some reason, compiling in debug mode was not setting DEBUG define, so I defined it in here, and uncommented when debugging was needed
#ifdef DEBUG

#include "include/Camera.h"
#include "include/Game.h"

#include <SDL2/SDL.h>
#endif // DEBUG

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated)
{
    this->scale = scale;
    this->offset = offset;
}

void Collider::Update(float dt){
    //Set collider box as associated box in scale
    box = associated.box;
    box.x -= ((box.w*scale.x) - box.w)/2 + Vec2::RotDeg(offset, associated.angleDeg).x;
    box.y -= ((box.h*scale.y) - box.h)/2 + Vec2::RotDeg(offset, associated.angleDeg).y;
    box.w *= scale.x;
    box.h *= scale.y;
    //box.RotateDg(associated.angleDeg);
}

void Collider::Render(){
#ifdef DEBUG
    Vec2 center( box.Center() );
    SDL_Point points[5];

    Vec2 point = (Vec2(box.x, box.y) - center).RotRad( associated.angleDeg/(180/PI) )
                    + center - Camera::pos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y) - center).RotRad( associated.angleDeg/(180/PI) )
                    + center - Camera::pos;
    points[1] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y + box.h) - center).RotRad( associated.angleDeg/(180/PI) )
                    + center - Camera::pos;
    points[2] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x, box.y + box.h) - center).RotRad( associated.angleDeg/(180/PI) )
                    + center - Camera::pos;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(string type){
    return (!type.compare("Collider"));
}

void Collider::SetScale(Vec2 scale){
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset){
    this->offset = offset;
}




