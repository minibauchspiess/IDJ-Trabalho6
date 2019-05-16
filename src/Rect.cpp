#include "include/Rect.h"

Rect::Rect()
{
}

Rect::Rect(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

//Moves the Rect object (x and y) by the given vector
void Rect::Move(Vec2 v){
    this->x = this->x + v.x;
    this->y = this->y + v.y;
}

//Provides the center of the Rect instance
Vec2 Rect::Center(){
    return Vec2( (this->x + (this->w)/2 ), (this->y + (this->h)/2 ) );
}

//Rotates box, with it's center as reference
void Rect::RotateDg(float dg){
    Vec2 newPos = Vec2::RotDeg(Vec2(this->x, this->y), this->Center(), dg);
    this->x = newPos.x;
    this->y = newPos.y;
}

//Gives the distance between the centers of a given Rect and itself
float Rect::DistRect(Rect r1){
    float x = r1.Center().x - this->Center().x;     //Distance in the x axis
    float y = r1.Center().y - this->Center().y;     //Distance in the y axis

    return sqrt(x*x + y*y);
}

//Returns true if a given point (vector) is inside the Rect object
bool Rect::IsIn(Vec2 v){
    return ((v.x >= this->x && v.x <= this->x + this->w) &&    //It must be inside the instance range in the x axis
            (v.y >= this->y && v.y <= this->y + this->h));      //And it must be inside the instance range in the y axis
}
