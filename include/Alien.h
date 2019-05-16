#ifndef ALIEN_H
#define ALIEN_H


//Alien atributes
#define ALIEN_HP 250
#define ALIEN_SPEED 200  //Module of the speed
#define ALIEN_ROT_SPD_DG -MINION_ROT_SPD_DG/2
#define ALIEN_REST_TIME 2


#include "Component.h"
#include "Gameobject.h"
#include "Sprite.h"
#include "Minion.h"
#include "PenguinBody.h"
#include "Collider.h"
#include "InputManager.h"
#include "Camera.h"
#include "Vec2.h"
#include "Timer.h"
#include <queue>
#include <vector>



using namespace std;

class Alien : public Component
{
public:
    Alien(GameObject& associated, int nMinions);
    ~Alien();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject &other);

    static int alienCount;

private:

    enum AlienState{MOVING, RESTING};
    AlienState state;
    Timer restTimer;
    Vec2 destination;

    /*class Action{

        public:
        enum ActionType {MOVE, SHOOT};
        Action(ActionType type, float x, float y);

        ActionType type;
        Vec2 pos;
    };*/

    int nMinions;
    Vec2 speed;
    int hp;
    //queue<Action> taskQueue;
    vector<weak_ptr<GameObject>> minionArray;
};

#endif // ALIEN_H
