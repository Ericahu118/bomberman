#ifndef PHYSICS_H
#define PHYSICS_H
#include <component.h>
#include <gameobject.h>
#include <transform.h>
#include "role.h"
class Physics : public Component
{
public:
    Physics();
    void onAttach() override;
    void onUpdate(float deltaTime) override;
    bool checkarea(int t);
    void setVelocity(float vx, float vy);
    void lastpoint(int i, int j);


private:
    Transform * transform;
    float vx = 0, vy = 0;
    Role * role;
    float deltax = 0, deltay = 0;
    int last_i = 0, last_j = 0;


};
#endif // PHYSICS_H
