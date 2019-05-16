#include "include/PenguinBody.h"
#include "include/Game.h"

PenguinBody *PenguinBody::player;

PenguinBody::PenguinBody(GameObject &associated) : Component (associated)
{
    //Variable initialization
    speed = Vec2(0,0);
    linearSpeed = 0;
    angle = 0;
    hp = PG_HP;
    player = this;

    //Create it's sprite
    Sprite *pgBdSprite = new Sprite(associated, "assets/img/penguin.png");
    associated.AddComponent(pgBdSprite);

    //Add collider to the object
    Collider* colider = new Collider(associated, Vec2(1,1), Vec2(0, 0));
    associated.AddComponent(colider);
}

PenguinBody::~PenguinBody(){
    player = nullptr;
}

void PenguinBody::Start(){
    //Create associated weak pointer
    //shared_ptr<GameObject> shAssociated(&associated);
    weak_ptr<GameObject> wBody = Game::GetInstance().GetState().GetObjectPtr(&associated);

    //Create cannon object
    GameObject *pgCannonObj = new GameObject();
    PenguinCannon *pgCannon = new PenguinCannon(*pgCannonObj, wBody);
    pgCannonObj->box.x = associated.box.Center().x - pgCannonObj->box.w/2;      //Put its center in penguin body center
    pgCannonObj->box.y = associated.box.Center().y - pgCannonObj->box.h/2;
    pgCannonObj->AddComponent(pgCannon);
    pcannon = Game::GetInstance().GetState().AddObject(pgCannonObj);
}

void PenguinBody::Update(float dt){
    InputManager &input = InputManager::GetInstance();
    //Change body speed if w or s is pressed
    if(input.IsKeyDown('w')||input.IsKeyDown('s')){
        if(input.IsKeyDown('w')){
            if(linearSpeed < PG_SPEED_CAP_FWD){
                linearSpeed += PG_ACEL*dt;
            }
            else{
                linearSpeed = PG_SPEED_CAP_FWD;
            }
        }
        if(input.IsKeyDown('s')){
            if(linearSpeed > -PG_SPEED_CAP_BACK){
                linearSpeed -= PG_ACEL*dt;
            }
            else{
                linearSpeed = -PG_SPEED_CAP_BACK;
            }
        }
    }
    else{                   //Makes the penguing go slower if not being acelerated
        if(abs(linearSpeed) > PG_SLOW_MIN){
            linearSpeed -= linearSpeed*PG_SLOW_CONST*dt;
        }
        else {
            linearSpeed = 0;
        }
    }


    //Rotate body if a or d is pressed
    if(input.IsKeyDown('a')){
        associated.angleDeg += PG_ROT_SPEED*dt;
    }
    if(input.IsKeyDown('d')){
        associated.angleDeg -= PG_ROT_SPEED*dt;
    }

    //Set new position
    speed = Vec2::Vec2Pol(associated.angleDeg, linearSpeed);
    associated.box.x += speed.x*dt;
    associated.box.y += speed.y*dt;

    //Delete it if hp it died
    if(hp <= 0){
        //Create death animation
        GameObject *pgDeathObj = new GameObject();
        Sprite *pgDeathSprite = new Sprite(*pgDeathObj, "assets/img/penguindeath.png", 5, 0.3, 4*0.3);
        Sound *pgDeathSound = new Sound(*pgDeathObj, "assets/audio/boom.wav");
        pgDeathSound->Play(1);
        pgDeathObj->box = associated.box;
        pgDeathObj->AddComponent(pgDeathSprite);
        pgDeathObj->AddComponent(pgDeathSound);
        Game::GetInstance().GetState().AddObject(pgDeathObj);

        //Delete itself
        associated.RequestDelete();
        pcannon.lock()->RequestDelete();
        Camera::Unfollow();
        cout<<"Passei aqui antes de crashar"<<endl;
    }
}

void PenguinBody::Render(){}

bool PenguinBody::Is(string type){
    return (!type.compare("PenguinBody"));
}

void PenguinBody::NotifyCollision(GameObject &other){
    Bullet *bullet = (Bullet*)other.GetComponent("Bullet").get();       //Pointer to the bullet that collided (if it wasn't a bullet, it'll be a nullptr)


    if(bullet && bullet->targetsPlayer){       //Check if it was a bullet and if it wasn't friendly fire
        hp -= bullet->GetDamage();
    }
    else{
        if(other.GetComponent("Alien").get() || other.GetComponent("Minion").get()){
            hp = 0;     //Die if collides with any alien or minion
        }
    }

}

Vec2 PenguinBody::GetPosition(){
    return this->associated.box.Center();
}

