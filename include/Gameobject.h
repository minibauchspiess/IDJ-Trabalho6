
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <vector>
#include <memory>
#include "Rect.h"

using namespace std;


class Component;

class GameObject
{
public:
    GameObject(int layer=0);
    ~GameObject();
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject &other);
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    shared_ptr<Component> GetComponent(string type);

    void Start();
    bool started;

    Rect box;
    int layer;      //Variable to place the render order

    double angleDeg;

private:
    vector<shared_ptr<Component>> components;
    bool isDead;
};

#endif // GAMEOBJECT_H
