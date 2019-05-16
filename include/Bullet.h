#ifndef BULLET_H
#define BULLET_H


#define BULLET_DMG 10
#define BULLET_SPEED 400
#define BULLET_DIST 1000

#include "Component.h"
#include "Gameobject.h"
#include "Sprite.h"
#include "Collider.h"

#include "Vec2.h"


using namespace std;

class Bullet : public Component
{
public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime, bool targetsPlayer);

    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject &other);

    int GetDamage();
    bool targetsPlayer;

private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};

#endif // BULLET_H
