#include "include/Component.h"

Component::Component(GameObject& associated) : associated(associated)
{
}

Component::~Component(){

}
void Component::Update(float dt){}
void Component::Render(){}
bool Component::Is(string type){}
void Component::Start(){}
void Component::NotifyCollision(GameObject &other){}
