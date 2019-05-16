//#define DEBUG

#include "include/Game.h"
#include "include/Rect.h"
#include "include/Vec2.h"
#include "include/Gameobject.h"

#include <vector>

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    Game& game = Game::GetInstance();
    game.Run();

    return 0;
}
