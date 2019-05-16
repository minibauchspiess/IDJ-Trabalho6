#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

//Defines to occult SDL names
#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT


#define INCLUDE_SDL
#include "SDL_include.h"


//Defines to some keys
#define LARROW SDLK_LEFT
#define RARROW SDLK_RIGHT
#define UARROW SDLK_UP
#define DARROW SDLK_DOWN
#define SPACE SDLK_SPACE
#define ESC SDLK_ESCAPE

#define LMOUSE SDL_BUTTON_LEFT
#define RMOUSE SDL_BUTTON_RIGHT



#include <unordered_map>

using namespace std;

class InputManager
{
public:
    static InputManager& GetInstance();

    void Update();

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);

    int GetMouseX();
    int GetMouseY();

    bool QuitRequested();

private:
    InputManager();
    ~InputManager();

    bool mouseState[6];
    int mouseUpdate[6];

    unordered_map<int, bool> keyState;
    unordered_map<int, int> keyUpdate;

    bool quitRequested;

    int updateCounter;

    int mouseX;
    int mouseY;
};

#endif // INPUTMANAGER_H
