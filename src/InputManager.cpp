#include "include/InputManager.h"

//For debugging
#include "iostream"
using namespace std;


InputManager::InputManager()
{
    for(int i=0; i<6; i++){
        mouseState[i] = 0;
        mouseUpdate[i] = 0;
    }

    quitRequested = 0;
    updateCounter = 0;

    mouseX = 0;
    mouseY = 0;
}

InputManager::~InputManager(){}

InputManager& InputManager::GetInstance(){
    static InputManager instance;
    return instance;
}

void InputManager::Update(){
    SDL_Event event;

    updateCounter++;

    //Get mouse position
    SDL_GetMouseState(&mouseX, &mouseY);

    //Reset quit flag, in case State processed it and didn't ended program
    quitRequested = false;

    //Check if an input was given
    while(SDL_PollEvent(&event)){

        //If it is a new event, processes it
        if(!event.key.repeat){

            //Identify what input was given, and execute corresponding action
            switch (event.type) {

                //Keyboard button was pressed
                case SDL_KEYDOWN:
                    keyState[event.key.keysym.sym] = true;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                    break;
                //Keyboard button was released
                case SDL_KEYUP:
                    keyState[event.key.keysym.sym] = false;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                    break;


                //Mouse button was pressed
                case SDL_MOUSEBUTTONDOWN:
                    mouseState[event.button.button] = true;
                    mouseUpdate[event.button.button] = updateCounter;
                    break;
                //Mouse button was released
                case SDL_MOUSEBUTTONUP:
                    mouseState[event.button.button] = false;
                    mouseUpdate[event.button.button] = updateCounter;
                    break;


                //Exit request was given
                case SDL_QUIT:
                    quitRequested = true;
                    break;
            }
        }
    }
}


//Methods to get keyboard button information
bool InputManager::KeyPress(int key){
    return keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key){
    return !keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key){
    return keyState[key];
}


//Methods to get mouse button information
bool InputManager::MousePress(int key){
    return mouseState[key] && (mouseUpdate[key] == updateCounter);
}

bool InputManager::MouseRelease(int key){
    return !mouseState[key] && (mouseUpdate[key] == updateCounter);
}

bool InputManager::IsMouseDown(int key){
    return mouseState[key];
}


//Methods to get mouse coordinates
int InputManager::GetMouseX(){
    return mouseX;
}

int InputManager::GetMouseY(){
    return  mouseY;
}



bool InputManager::QuitRequested(){
    return quitRequested;
}

