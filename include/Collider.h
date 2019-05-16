#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"
#include "Gameobject.h"

#include "Vec2.h"
#include "Rect.h"

using namespace std;
class Collider : public Component
{
public:
    Collider(GameObject& associated, Vec2 scale = Vec2(1,1), Vec2 offset = Vec2(0,0));

    Rect box;

    void Update(float dt);
    void Render();
    bool Is(string type);


    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);

private:
    Vec2 scale;
    Vec2 offset;
};
#endif // COLLIDER_H
