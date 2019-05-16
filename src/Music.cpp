#include "include/Music.h"
#include "include/Resources.h"
#include <iostream>

using namespace std;

Music::Music()
{
    music = nullptr;
}

Music::Music(std::string file){
    Open(file);
}

void Music::Play(int times){
    Mix_PlayMusic(music, times);
}

void Music::Stop(int msToStop){
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file){
    music = Resources::GetMusic(file);
    if (music == nullptr){
        cout<<"No music was loaded"<<endl;
    }
}

bool Music::IsOpen(){
    if (music == nullptr){
        return false;
    }
    else{
        return true;
    }
}

Music::~Music(){
    Stop(10);
}
