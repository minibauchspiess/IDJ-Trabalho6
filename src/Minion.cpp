#include "include/Minion.h"
#include "include/Game.h"

Minion::Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component (associated), alienCenter(alienCenter), arc(arcOffsetDeg)
{
    //Add the minion image to the object
    Sprite* minionFace = new Sprite(associated, "assets/img/minion.png");
    associated.AddComponent(minionFace);

    //Add collider to the object
    Collider* colider = new Collider(associated);
    associated.AddComponent(colider);

    //Create shared pointer from the weak given
    shared_ptr<GameObject> alien = this->alienCenter.lock();

    //Place it near alien
    Vec2 aux = Vec2(MINION_DIST, 0);
    aux.RotRad(arc);
    this->associated.box.x = alien->box.x + aux.x - associated.box.w/2;
    this->associated.box.y = alien->box.y + aux.y - associated.box.h/2;
}

void Minion::Update(float dt){
    //Create shared pointer from the weak given
    shared_ptr<GameObject> alien = alienCenter.lock();

    //Rotate minion
    this->associated.angleDeg += MINION_ROT_SPD_DG*dt;

    //Check if pointer still exists
    if(!alien){
        associated.RequestDelete();     //If alien was deleted, delet minion too
    }
    else{                               //Else, update it's position

        Vec2 aux = Vec2(MINION_DIST, 0);
        arc = arc + MINION_TR_SPD*dt;
        aux = aux.RotRad(arc);
        this->associated.box.x = alien->box.Center().x + (aux.x - associated.box.w/2);
        this->associated.box.y = alien->box.Center().y + (aux.y - associated.box.h/2);
    }
}

void Minion::Render(){}

bool Minion::Is(string type){
    return (!type.compare("Minion"));
}

void Minion::Shoot(Vec2 target){
    float angRad = Vec2::IncRad( associated.box.Center(), target );

    //Create the bullet object
    GameObject *bulletObj = new GameObject();
    Bullet *bullet = new Bullet(*bulletObj, angRad, BULLET_SPEED, BULLET_DMG, BULLET_DIST, "assets/img/minionbullet2.png", 3, 0.1, true);
    bulletObj->AddComponent(bullet);
    bulletObj->box.x = associated.box.Center().x -  bulletObj->box.w/2;
    bulletObj->box.y = associated.box.Center().y -  bulletObj->box.h/2;
    Game::GetInstance().GetState().AddObject(bulletObj);
}

void Minion::NotifyCollision(GameObject &other){}
