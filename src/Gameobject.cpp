#include "include/Gameobject.h"
#include "include/Component.h"



GameObject::GameObject(int layer)
{
    started = false;
    isDead = false;
    this->layer = layer;
    angleDeg = 0;
}

GameObject::~GameObject(){
    components.clear();
}

void GameObject::Start(){
    //Start all components
    for(unsigned int i=0; i<components.size(); i++){
        components[i]->Start();
    }
    started = true;

}

void GameObject::Update(float dt){
    for (int i = 0; i<components.size(); i++){
        components[i]->Update(dt);
    }
}

void GameObject::Render(){
    for (int i = 0; i<components.size(); i++){
        components[i]->Render();
    }
}

bool GameObject::IsDead(){
    return isDead;
}

void GameObject::RequestDelete(){
    isDead = true;
}

void GameObject::AddComponent(Component* cpt){
    components.emplace_back(cpt);

    //Start the component if the components vector has already been started
    if(started) cpt->Start();
}

void GameObject::RemoveComponent(Component* cpt){
    for (int i = 0; i < components.size();){
        if (components[i].get() == cpt){
            components.erase(components.begin() + i);
            break;
        }
        else{
            i++;
        }
    }
}

shared_ptr<Component> GameObject::GetComponent(string type){
    for (int i = 0; i < components.size(); i++){
        if (components[i]->Is(type)){
            return components[i];
        }
    }
    return nullptr;
}

void GameObject::NotifyCollision(GameObject &other){
    for (unsigned int i=0; i<components.size(); i++){
        components[i]->NotifyCollision(other);
    }
}
