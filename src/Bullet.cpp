#include "include/Bullet.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime, bool targetsPlayer) :  Component(associated)
{
    //Add sprite component
    Sprite* bSprite = new Sprite(associated, sprite, frameCount, frameTime);
    associated.AddComponent(bSprite);

    //Add collider to the object
    Collider* colider = new Collider(associated, Vec2(1,1), Vec2(-associated.box.w/2, 0));
    associated.AddComponent(colider);

    //Initialize variables
    this->speed = Vec2(speed, 0);
    this->speed = this->speed.RotRad(angle);
    distanceLeft = maxDistance;
    this->damage = damage;
    this->targetsPlayer = targetsPlayer;

    //Set orientation of go
    associated.angleDeg = angle * (180/PI);
}

void Bullet::Update(float dt){
    Vec2 step = Vec2::Mul(speed, dt);               //Calculate the step
    distanceLeft = distanceLeft - Vec2::Mag(step);  //Atualize bullet lifetime
    if(distanceLeft>0){                             //Move it if it still has distance to move
        associated.box.x = associated.box.x + step.x;
        associated.box.y = associated.box.y + step.y;
    }
    else{
        associated.RequestDelete();
    }
}

void Bullet::Render(){}

bool Bullet::Is(string type){
    return (!type.compare("Bullet"));
}

int Bullet::GetDamage(){
    return damage;
}

void Bullet::NotifyCollision(GameObject &other){
    if((!other.GetComponent("Bullet"))){
        if((other.GetComponent("PenguinBody") && targetsPlayer) || (other.GetComponent("PenguinCannon") && targetsPlayer) || (other.GetComponent("Minion") && !targetsPlayer) || (other.GetComponent("Alien") && !targetsPlayer)){
            associated.RequestDelete();
        }
    }
}








