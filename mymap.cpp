#include <gameobject.h>
#include <transform.h>
#include <transformbuilder.h>
#include <cstring>

#include"mymap.h"


int Map[ROW][COL] = {{1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                     {2, 11, 0, 2, 3, 0, 0, 0, 0, 3, 3, 4, 2, 5, 3, 2, 4, 3, 12, 2},
                     {2, 0, 0, 5, 3, 0, 2, 0, 2, 2, 0, 0, 0, 0, 4, 2, 5, 0, 0, 2},
                     {2, 0, 0, 0, 0, 0, 4, 0, 3, 4, 5, 0, 0, 0, 2, 2, 3, 0, 0, 2},
                     {2, 3, 0, 3, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 5, 2},
                     {2, 5, 3, 4, 4, 2, 0, 2, 6, 0, 0, 0, 2, 0, 0, 0, 0, 4, 3, 2},
                     {2, 3, 4, 4, 2, 4, 0, 2, 0, 0, 0, 0, 2, 0, 4, 5, 2, 5, 3, 2},
                     {2, 2, 2, 3, 2, 5, 0, 2, 0, 0, 0, 0, 2, 0, 2, 4, 3, 2, 2, 2},
                     {2, 0, 0, 0, 2, 4, 0, 2, 0, 0, 0, 0, 2, 0, 2, 0, 3, 4, 3, 2},
                     {2, 5, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 2, 0, 0, 0, 4, 2},
                     {2, 2, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 5, 2, 2},
                     {2, 0, 0, 0, 0, 3, 3, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 5, 2},
                     {2, 0, 21, 5, 5, 0, 4, 2, 0, 5, 0, 0, 0, 5, 4, 0, 22, 0, 3, 2},
                     {2, 0, 0, 2, 5, 0, 5, 5, 4, 3, 2, 4, 2, 5, 3, 0, 0, 0, 4, 2},
                     {1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1}};
int Tool[ROW][COL] = {0};
void createmap(){
   srand(time(0));
  for(int i = 1;i<=randd;i++){
      int x = rand()%ROW;
      int y = rand()%COL;
      if(Map[x][y] >=3 && Map[x][y] <= 5){
          Tool[x][y]=rand()%10 + 1;
      }
  }

}

