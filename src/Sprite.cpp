
#include "include/Sprite.h"
#include "include/Game.h"
#include "include/Resources.h"
#include <iostream>

using namespace std;

Sprite::Sprite(GameObject& associated) : Component(associated)
{
    texture = nullptr;
    scale = Vec2(1, 1);
    angleDeg = associated.angleDeg;
}

Sprite::Sprite(GameObject& associated, string file, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(associated){

    scale = Vec2(1, 1);
    angleDeg = associated.angleDeg;

    this->frameCount = frameCount;
    this->frameTime = frameTime;
    currentFrame = 0;
    timeElapsed = 0;
    this->secondsToSelfDestruct = secondsToSelfDestruct;
    selfDestructCount = Timer();

    texture =nullptr;
    Open(file);
}

Sprite::~Sprite(){
}

void Sprite::Update(float dt){
    timeElapsed += dt;

    //Select frame based on time elapsed
    if(timeElapsed > frameTime*(currentFrame+1)){     //First frame is 0
        //Pass to next frame
        if((currentFrame+1) >= frameCount){         //Check if it is the last frame
            currentFrame = 0;
            timeElapsed = 0;                        //Timer restarts every time it passes through the hole sprite
        }
        else{
            currentFrame += 1;
        }

        //Set new frame clip
        SetClip(currentFrame*clipRect.w, clipRect.y, clipRect.w, clipRect.h);
    }

    //Check if sprite has timeout
    if(secondsToSelfDestruct != 0){
        //Check if it has expired
        if(selfDestructCount.Get() < secondsToSelfDestruct){
            selfDestructCount.Update(dt);
        }
        else {
            associated.RequestDelete();
        }
    }
}

bool Sprite::Is(string type){
    return (!type.compare("sprite"));
}

void Sprite::Open(string file){

    int width, height;

    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    width = width/frameCount;
    associated.box.w = width;
    associated.box.h = height;
    SetClip(currentFrame*associated.box.w, 0, width, height);

}

void Sprite::SetClip(int x, int y, int w, int h){
    clipRect.x=x;
    clipRect.y=y;
    clipRect.w=w;
    clipRect.h=h;
}

void Sprite::Render(){
    Render(associated.box.x, associated.box.y, associated.box.w, associated.box.h);
}

void Sprite::Render(int x, int y, int w, int h, int layer){
    Game& instance = Game::GetInstance();

    SDL_Rect dstrect;
    dstrect.x = x - (int)(Camera::pos.x*(layer+1)*LAYER_MOV);
    dstrect.y = y - (int)(Camera::pos.y*(layer+1)*LAYER_MOV);

    dstrect.w = w;
    dstrect.h = h;

    SDL_RenderCopyEx(instance.GetRenderer(), texture, &clipRect, &dstrect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

int Sprite::GetWidth(){
    return (associated.box.w * scale.x) / this->frameCount;
}

int Sprite::GetHeight(){
    return associated.box.h * scale.y;
}

bool Sprite::IsOpen(){
    if (texture != nullptr){
        return true;
    }
    else{
        return false;
    }
}

void Sprite::SetScale(float scaleX, float scaleY){
    if(scaleX){     //Any value different than 0 changes the scale
        scale.x = scaleX;
    }
    if(scaleY){
        scale.y = scaleY;
    }

    //Adjust object box with scale
    associated.box.x = associated.box.x - ((associated.box.w * scale.x) - associated.box.w)/2;
    associated.box.y = associated.box.y - ((associated.box.h * scale.y) - associated.box.h)/2;

    associated.box.w = associated.box.w * scale.x;
    associated.box.h = associated.box.h * scale.y;
}

Vec2 Sprite::GetScale(){
    return scale;
}

void Sprite::SetFrame(int frame){
    currentFrame = frame;
    SetClip(currentFrame*clipRect.w, clipRect.y, clipRect.w, clipRect.h);
}

void Sprite::SetFrameCount(int frameCount){
    float oldWidth = associated.box.w;      //Variable that considers earlyer width and scale
    int oldFrameCount = this->frameCount;

    this->frameCount = frameCount;
    currentFrame = 0;
    associated.box.x = 0;
    associated.box.y = 0;
    associated.box.w = (oldWidth*oldFrameCount) / frameCount;
    //This changes nothing in the image height
}

void Sprite::SetFrameTime(float frameTime){
    this->frameTime = frameTime;
}





