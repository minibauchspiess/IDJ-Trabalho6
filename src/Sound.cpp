#include "include/Sound.h"
#include "include/Resources.h"

Sound::Sound(GameObject& associated) : Component (associated)
{
    chunk = nullptr;
}

Sound::Sound(GameObject& associated, string file) : Sound(associated)
{
   Open(file);
}

void Sound::Play(int times){
    channel = Mix_PlayChannel(-1, chunk, times-1);
}

void Sound::Stop(){
    if (chunk != nullptr){
        Mix_HaltChannel(channel);
    }
}


void Sound::Open(string file){
    chunk = Resources::GetSound(file);
}

bool Sound::Is(string type){
    return !type.compare("sound");
}

void Sound::Update(float dt){}

void Sound::Render(){}

Sound::~Sound(){
    if (chunk != nullptr){
        //while (Mix_Playing(channel));
        Mix_HaltChannel(channel);
    }
}
