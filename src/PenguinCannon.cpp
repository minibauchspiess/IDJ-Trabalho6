#include "include/PenguinCannon.h"
#include "include/Game.h"

PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody) : Component (associated)
{
    //Variable initialization
    pbody = penguinBody;
    angle = 0;
    timer = Timer();

    //Associate a sprite to it
    Sprite *pgCanSprite = new Sprite(associated, "assets/img/cubngun.png");
    associated.AddComponent(pgCanSprite);

    //Add collider to the object
    Collider* colider = new Collider(associated);
    associated.AddComponent(colider);
}

void PenguinCannon::Update(float dt){
    InputManager &input = InputManager::GetInstance();
    shared_ptr<GameObject> shPg = pbody.lock();

    timer.Update(dt);

    //Check if body was destroyed
    if(shPg.get() == nullptr){
        associated.RequestDelete();
    }
    else{
        //Make cannon follow body center
        associated.box.x = pbody.lock()->box.Center().x - associated.box.w/2;
        associated.box.y = pbody.lock()->box.Center().y - associated.box.h/2;
       //Rotate cannon to aim the mouse position
        associated.angleDeg = Vec2::IncDg(Vec2::Sub(Vec2(input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y), Vec2(associated.box.x+associated.box.w/2, associated.box.y+associated.box.h/2)));       //Get inclination from line that goes from the GO to the mouse position
        //Shoot if left mouse button was pressed
        if(input.IsMouseDown(LMOUSE)){
            if(timer.Get() > (float)1/PG_SHOOT_SPEED){
                Shoot();
                timer.Restart();
            }
        }
    }
}

void PenguinCannon::Render(){}

bool PenguinCannon::Is(string type){
    return (!type.compare("PenguinCannon"));
}

void PenguinCannon::Shoot(){
    //Create the bullet object
    GameObject *bulletObj = new GameObject();
    Bullet *bullet = new Bullet(*bulletObj, associated.angleDeg * (PI/180), BULLET_SPEED, BULLET_DMG, BULLET_DIST, "assets/img/penguinbullet.png", 4, 0.2, false);
    bulletObj->AddComponent(bullet);
    bulletObj->box.x = associated.box.Center().x -  bulletObj->box.w/2 + Vec2::RotDeg(Vec2(associated.box.w/2, 0), associated.angleDeg).x;
    bulletObj->box.y = associated.box.Center().y -  bulletObj->box.h/2 + Vec2::RotDeg(Vec2(associated.box.w/2, 0), associated.angleDeg).y;
    Game::GetInstance().GetState().AddObject(bulletObj);
}




