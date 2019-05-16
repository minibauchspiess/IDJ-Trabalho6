
#ifndef STATE_H
#define STATE_H


#define N_LAYERS 2

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "Music.h"
#include "Sprite.h"
#include "Collider.h"
#include "Collision.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include <memory>

using namespace std;

class State
{
public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();

    //void Input();
    weak_ptr<GameObject> AddObject(GameObject* go);
    weak_ptr<GameObject> GetObjectPtr(GameObject* go);

private:
    //Sprite bg;
    Music music;

    bool quitRequested;
    bool started;

    vector<shared_ptr<GameObject>> objectArray;
};

#endif
