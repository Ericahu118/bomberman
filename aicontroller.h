#ifndef AICONTROLLER_H
#define AICONTROLLER_H
#include <component.h>
#include <gameobject.h>
#include "physics.h"
#include <transformbuilder.h>

class AIController : public Component
{
public :
AIController ( int type) ;

void onAttach ( ) override ;
void onUpdate ( float deltaTime ) override ;
void tochange(int dir);
int getdir();
bool checkboom(int x, int area);
int getstaydir();
void changestaydir();
bool checkobstacle();
int gettype();
int searchmap(int i, int j);

private :
Physics * physics ;
ImageTransform* imagetransform;
int dir = 0;
int type;
float putbomb= 9;
int staydir = 0;

Transform* transform;
} ;
#endif // AICONTROLLER_H
