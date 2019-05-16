
#ifndef COMPONENT_H
#define COMPONENT_H




#include "Gameobject.h"

#include <iostream>


using namespace std;


class Component
{
public:
    Component(GameObject& associated);
    virtual ~Component() = 0;
    void virtual Update(float dt);
    void virtual Render() = 0;
    bool virtual Is(string type) = 0;
    void virtual Start();
    void virtual NotifyCollision(GameObject &other);

protected:
    GameObject& associated;
    std::string component_type;
};

#endif // COMPONENT_H
