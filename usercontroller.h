#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H
#include <component.h>
#include <gameobject.h>
#include "physics.h"
#include <transformbuilder.h>
class UserController : public Component
{
public :
UserController ( ) ;

void onAttach ( ) override ;
void onUpdate ( float deltaTime ) override ;
void setcontroller(int use);
int gettype();

private :
Physics * physics ;
ImageTransform* imagetransform;//add
int controller;//add
int last_dir = 0;
Transform* transform;
} ;

#endif // USERCONTROLLER_H
