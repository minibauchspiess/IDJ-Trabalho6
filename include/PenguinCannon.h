#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

#define PG_SHOOT_SPEED 5    //3 bullets per second

#include "Component.h"
#include "Gameobject.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Collider.h"
#include "InputManager.h"
#include "Timer.h"

using namespace std;

class PenguinCannon : public Component
{
public:
    PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody);

    void Update(float dt);
    void Render();
    bool Is(string type);

    void Shoot();

private:
    weak_ptr<GameObject> pbody;
    float angle;
    Timer timer;
};

#endif // PENGUINCANNON_H
