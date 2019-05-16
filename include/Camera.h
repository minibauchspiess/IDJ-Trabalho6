#ifndef CAMERA_H
#define CAMERA_H

#include "Gameobject.h"
#include "Vec2.h"
#include "InputManager.h"


//Movement
#define SPEED 150

class Camera
{
public:
    Camera();

    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);

    static Vec2 pos;
    static Vec2 speed;

private:
    static GameObject* focus;
};

#endif // CAMERA_H
