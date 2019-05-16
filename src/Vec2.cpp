#include "include/Vec2.h"


using namespace std;

Vec2::Vec2()
{

}

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

//Creates a vector with given polar parameters (angle and magnitude)
Vec2 Vec2::Vec2Pol(float dg, float mag){
    return RotDeg(Vec2(mag, 0), dg);
}

//Returns the sum of two vectors
Vec2 Vec2::Add(Vec2 v1, Vec2 v2){
    return Vec2(v1.x + v2.x, v1.y + v2.y);
}

//Returns the first vector given by the second vector given
Vec2 Vec2::Sub(Vec2 v1, Vec2 v2){
    return Vec2(v1.x - v2.x, v1.y - v2.y);
}

//Multiply the vector by an scalar
Vec2 Vec2::Mul(Vec2 v1, float a){
    return Vec2(a * v1.x, a * v1.y);
}

//Returns the magnitude of a vector
float Vec2::Mag(Vec2 v){
    return sqrt((v.x)*(v.x) + (v.y)*(v.y));
}

//Given a vector, returns its unit form
Vec2 Vec2::Unit(Vec2 v){
    float mag = Mag(v);
    return Vec2(v.x/mag, v.y/mag);
}

//Returns the distance between two points (distance between two vectors)
float Vec2::Dist(Vec2 v1, Vec2 v2){
    return Mag(Sub(v1, v2));
}

//Returns the inclination of the vector in radians
float Vec2::IncRad(Vec2 v1){
    return atan2(v1.y, v1.x);
}

float Vec2::IncRad(Vec2 v1, Vec2 v2){
    return atan2((v2.y - v1.y), (v2.x - v1.x));
}

//Returns the inclination of the vector in degrees
float Vec2::IncDg(Vec2 v1){
    return IncRad(v1)*(180/PI);
}

float Vec2::IncDg(Vec2 v1, Vec2 v2){
    return IncRad(v1, v2)*(180/PI);
}

//Rotates the vector (it self) the specified amount of degrees
Vec2 Vec2::RotDeg(float degree){
    float rad = (degree * PI)/180;    //Converting the degrees given to radians
    return Vec2((this->x * cos(rad) - this->y * sin(rad)), (this->y * cos(rad) + this->x * sin(rad)));
}

//Rotate the vector the specified amount of degrees
Vec2 Vec2::RotDeg(Vec2 v1, float degree){
    float rad = (degree * PI)/180;    //Converting the degrees given to radians
    return Vec2((v1.x * cos(rad) - v1.y * sin(rad)), (v1.y * cos(rad) + v1.x * sin(rad)));
}

//Rotate the vector (v1) given a reference point
Vec2 Vec2::RotDeg(Vec2 v1, Vec2 v2, float degree){
    float rad = (degree * PI)/180;    //Converting the degrees given to radians

    Vec2 vaux = Sub(v1, v2);
    vaux = Vec2((vaux.x * cos(rad) - vaux.y * sin(rad)), (vaux.y * cos(rad) + vaux.x * sin(rad)));
    vaux = Add(vaux, v2);
    return vaux;
}

Vec2 Vec2::operator+(Vec2 v){
    return Vec2(this->x + v.x, this->y + v.y);
}

Vec2 Vec2::operator-(Vec2 v){
    return Vec2(this->x - v.x, this->y - v.y);
}

Vec2 Vec2::operator*(float a){
    return Vec2(this->x * a, this->y * a);
}

Vec2 Vec2::operator/(float a){
    return Vec2(this->x/a, this->y/a);
}


//Rotates the vector (it self) the specified amount of radians
Vec2 Vec2::RotRad(float rads){
    return Vec2((this->x * cos(rads) - this->y * sin(rads)), (this->y * cos(rads) + this->x * sin(rads)));
}

//Rotate the vector the specified amount of radians
Vec2 Vec2::RotRad(Vec2 v1, float rads){
    return Vec2((v1.x * cos(rads) - v1.y * sin(rads)), (v1.y * cos(rads) + v1.x * sin(rads)));
}

//Rotate the vector (v1) given a reference point
Vec2 Vec2::RotRad(Vec2 v1, Vec2 v2, float rads){

    Vec2 vaux = Sub(v1, v2);
    vaux = Vec2((vaux.x * cos(rads) - vaux.y * sin(rads)), (vaux.y * cos(rads) + vaux.x * sin(rads)));
    vaux = Add(vaux, v2);
    return vaux;
}
