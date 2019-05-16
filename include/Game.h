
#ifndef GAME_H
#define GAME_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"

#include "State.h"
#include "InputManager.h"


//For debugging
#include <iostream>
using namespace std;

class Game
{
    private:
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;
        Game(std::string title, int width, int height);

        int frameStart=0;
        float dt;
        void CalculateDeltaTime();

        int wWidth;
        int wHeight;

    public:
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
        ~Game();

        float GetDeltaTime();
        int GetWindowWidth();
        int GetWindowHeight();
};

#endif
