#ifndef SOUND_H
#define SOUND_H

#include "Component.h"

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>

using namespace std;

class Sound : public Component
{
public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, string file);
    ~Sound();

    void Play(int times);
    void Stop();
    void Open(string file);
    bool IsOpen();

    void Update(float dt);
    void Render();
    bool Is(string type);

private:
    Mix_Chunk* chunk;
    int channel;
};

#endif // SOUND_H
