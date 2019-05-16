#ifndef MINION_H
#define MINION_H

#define MINION_DIST 200
#define MINION_TR_SPD PI/2 //90º per second
#define MINION_ROT_SPD_DG MINION_TR_SPD*(180/PI)

#include "Gameobject.h"
#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include "Bullet.h"

#include "Vec2.h"

using namespace std;

class Minion : public Component
{
public:
    Minion(GameObject &associated, weak_ptr<GameObject>, float arcOffsetDeg = 0);

    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject &other);

    void Shoot(Vec2 target);

private:
    weak_ptr<GameObject> alienCenter;
    float arc;
};

#endif // MINION_H
