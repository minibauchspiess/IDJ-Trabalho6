#include "include/State.h"
#include "dirent.h"
#include "include/Vec2.h"
#include "include/Rect.h"
#include "include/Face.h"
#include "include/Sound.h"

#define PI 3.14159265358979323846

using namespace std;



State::State()
{

    started = false;

    //Background object
    GameObject* bgObj = new GameObject();
    Sprite* bg = new Sprite(*bgObj, "assets/img/ocean.jpg");
    bgObj->AddComponent(bg);
    CameraFollower* bgCamera = new CameraFollower(*bgObj);
    bgObj->AddComponent(bgCamera);
    AddObject(bgObj);


    //TileMap object
    GameObject* tmObj = new GameObject(-1);                     //Layer -1 tels state it is the TileMap object
    TileSet* ts = new TileSet(*tmObj, 64, 64, "assets/img/tileset.png");
    TileMap* tm = new TileMap(*tmObj, "assets/map/tileMap.txt", ts);
    tmObj->AddComponent(tm);
    tmObj->box.x = 0;
    tmObj->box.y = 0;
    AddObject(tmObj);

    //Alien
    GameObject* alObj = new GameObject();
    Alien* alien = new Alien(*alObj, 6);
    alObj->AddComponent(alien);
    alObj->box.x = 512;
    alObj->box.y = 300;
    AddObject(alObj);

    //Penguin -> player
    GameObject *pgObj = new GameObject();
    PenguinBody *pg = new PenguinBody(*pgObj);
    pgObj->AddComponent(pg);
    pgObj->box.x = 704;
    pgObj->box.y = 640;
    AddObject(pgObj);
    Camera::Follow(pgObj);


    quitRequested = false;

    music.Open("assets/audio/stageState.ogg");
    music.Play();
}

State::~State(){
    objectArray.clear();
}

void State::Start(){
    LoadAssets();

    //Calls Start of every object already in the vector
    for(unsigned int i=0;i<objectArray.size();i++){
        objectArray[i]->Start();
    }

    started = true;
}

void State::LoadAssets(){
    //Load things the game need
}

void State::Update(float dt){
    InputManager& input = InputManager::GetInstance();

    //Update camera position
    Camera::Update(dt);

    //Check user request to end program
    if(input.QuitRequested() || input.KeyPress(ESC)){
        quitRequested = true;
    }

    for (unsigned int i = 0; i < objectArray.size();){
        objectArray[i]->Update(dt);

        if (objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin()+i);
        }
        else{
            i++;
        }
    }

    for (unsigned int i = 0; i < objectArray.size();i++){
        for (unsigned int j=i+1;j<objectArray.size();j++) {
            Collider *colA = (Collider*)objectArray[i]->GetComponent("Collider").get();
            Collider *colB = (Collider*)objectArray[j]->GetComponent("Collider").get();
            if(colA && colB){
                if(Collision::IsColliding(colA->box, colB->box, objectArray[i]->angleDeg, objectArray[j]->angleDeg)){
                    objectArray[i]->NotifyCollision(*objectArray[j]);
                    objectArray[j]->NotifyCollision(*objectArray[i]);
                }
            }

        }
    }
}

void State::Render(){
    for (int layer=0; layer<N_LAYERS;layer++) {         //Render objects with layer priority
        for (unsigned int i = 0; i < objectArray.size(); i++){
            if(objectArray[i]->layer == -1){            //TileMap, a multilayer GameObject
                objectArray[i]->layer = layer;
                objectArray[i]->Render();
            }
            else{
                if(layer == objectArray[i]->layer){
                    objectArray[i]->Render();
                }
            }

        }
    }

}

bool State::QuitRequested(){
    return quitRequested;
}


weak_ptr<GameObject> State::AddObject(GameObject* go){
    //Create shared pointer with given pointer
    shared_ptr<GameObject> shgo(go);

    //Insert it in the vector of game objects
    objectArray.push_back(shgo);

    //Start the new object
    if(started) shgo->Start();

    //Return it as a weak pointer
    weak_ptr<GameObject> wgo(shgo);
    return wgo;
}


weak_ptr<GameObject> State::GetObjectPtr(GameObject *go){

    weak_ptr<GameObject> wgo;

    //Look for the game object in the vector of game objects
    for(unsigned i=0; i<objectArray.size(); i++) {
        if(objectArray[i].get() == go){
            wgo = objectArray[i];
            return wgo;
        }
    }

    return wgo;
}










