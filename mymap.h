#ifndef MYMAP_H
#define MYMAP_H

#include "component.h"
#include "gameobject.h"
const int ROW = 15;
const int COL = 20;
const int randd = 150;
const int block_size = 40;
const int role_widge = 25;
const int role_height = 35;


extern int Map[ROW][COL];
extern int Tool[ROW][COL];

void createmap();


#endif // MYMAP_H
