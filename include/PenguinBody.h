#ifndef PENGUINBODY_H
#define PENGUINBODY_H

#define PG_ACEL 80                              //Aceleration of the penguin
#define PG_SPEED_CAP_FWD 300                    //Maximum speed forward possible
#define PG_SPEED_CAP_BACK PG_SPEED_CAP_FWD/2    //Maximum speed forward possible
#define PG_SLOW_CONST 0.5                       //Penguin gets slower if not acelerated
#define PG_SLOW_MIN 10                          //Peguin stops fully if slowing bellow this threshold
#define PG_ROT_SPEED -90                        //Angular speed, in degrees per second
#define PG_HP 50                                //Penguin health


#include "Gameobject.h"
#include "Component.h"
#include "Sprite.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "InputManager.h"
#include "Vec2.h"

using namespace std;

class PenguinBody : public Component
{
public:
    PenguinBody(GameObject& associated);
    ~PenguinBody();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject &other);

    static PenguinBody *player;
    Vec2 GetPosition();

private:
    weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;
};

#endif // PENGUINBODY_H
