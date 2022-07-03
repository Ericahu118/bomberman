#include "aicontroller.h"
#include "shooter.h"
#include "hitable.h"
#include <QDebug>
#include "role.h"
#include "Obstacle.h"
#include "tool.h"
#include "time.h"
#include "mymap.h"
#include"gameobject.h"
#include "gamescene.h"
#include "transform.h"
#include <queue>
#include <QDebug>
using namespace std;
const int MAX = 15*20+5;
using namespace std;
int flag111 = 1;
AIController ::AIController(int type)
{
    srand(time(0));
    this->type = type;
    this->dir = 3 ;
};
void AIController ::onAttach()
{
    physics = this->gameObject->getComponent<Physics>();
    imagetransform = this->gameObject->getComponent<ImageTransform>();
    transform = this->gameObject->getComponent<Transform>();
    assert(imagetransform != nullptr);
    assert(physics != nullptr);
    assert(transform != nullptr);
}
void AIController ::tochange(int dir)
{
    this->dir = dir;
}
int AIController::getdir()
{
    return this->dir;
}
int AIController::getstaydir()
{
    return this->staydir;
}
void AIController::changestaydir()
{
    staydir = 0;
}
int AIController:: gettype(){
    return this->type;
}
bool AIController::checkobstacle(){
    for (auto item : transform->collidingItems())
    {
        while (item->parentItem() != nullptr)
            item = item->parentItem();
        auto transform1 = dynamic_cast<Transform *>(item);
        if (transform1 == nullptr)
            continue;
        auto gameObject1 = transform1->getParentGameObject();
        auto obstacle = gameObject1->getComponent<Obstacle>();
        auto tools = gameObject1->getComponent<Tools>();
        if (obstacle == nullptr)
        {
            continue;
        }
        else
        {
            if (tools == nullptr && obstacle != nullptr)
            {

                return false;
            }
        }
    }
    return true;
}
bool AIController::checkboom(int x, int area)
{
    bool flag = false;
    if (x == 0)
    {

        for (int i = 1; i <= 1 + area; i++)
        {
            transform->moveBy(0,-i*40);
            flag = checkobstacle();
            transform->moveBy(0, i*40);
            if(!flag){
                return flag;
            }
        }
        return true;
    }
    else if (x == 1)
    {
        for (int i = 1; i <= 1 + area; i++)
        {
            transform->moveBy(0,i*40);
            flag = checkobstacle();
            transform->moveBy(0, -i*40);
            if(!flag){
                return flag;
            }
        }
        return true;
    }
    else if (x == 2)
    {
        for (int i = 1; i <= 1 + area; i++)
        {
            transform->moveBy(-i*40,0);
            flag = checkobstacle();
            transform->moveBy(i*40,0);
            if(!flag){
                return flag;
            }
        }
        return true;
    }
    else
    {
        for (int i = 1; i <= 1 + area; i++)
        {
            transform->moveBy(i*40,0);
            flag = checkobstacle();
            transform->moveBy(-i*40,0);
            if(!flag){
                return flag;
            }
        }
        return true;
    }
}
int AIController::searchmap(int i, int j){
    //传入格点的行数和列数

   for(int  k= 0;k<ROW;k++){
        for(int r = 0;r<COL;r++){
            if(Map[k][r] == 11 || Map[k][r] == 12) Map[k][r]=0;
        }
    }
    auto scene = this->gameObject->gameScene;
    if(role1 != 0){
    auto player1 = scene->getGameObject("player1");
    float x1 = player1->getComponent<Transform>()->x();
    float y1 = player1->getComponent<Transform>()->y();
    if(Map[int(y1/40)][int(x1/40)] == 0) {
        Map[int(y1/40)][int(x1/40)]=11;
        //qDebug() << "11:" << int(y1/40) << " " << int(x1/40);
     }
    }
    if(role2 != 0){
        auto player2 = scene->getGameObject("player2");
        float x2 = player2->getComponent<Transform>()->x();
        float y2 = player2->getComponent<Transform>()->y();
        if(Map[int(y2/40)][int(x2/40)] == 0){
            Map[int(y2/40)][int(x2/40)]=12;
            //qDebug() << "12:" << int(y2/40) << " " << int(x2/40);
         }
    }
    //11， 12代表玩家，以上更新玩家位置
    if(Map[i][j] == 0){

    int visited[ROW+5][COL+5] = {0};//标记数组
    queue< pair<int, int> >  q;//队列
    int path[ROW+5][COL+5] = {0};//记录玩家到这个点的上一个方向
    int targetx = -1, targety = -1;//初始目标点
        visited[i][j] = 1;
        pair<int, int> v;
        v.first = i, v.second = j;//对v做已访问标记
        q.push(v);    //顶点v入队列Q
        path[i][j] = 0;
        while(!q.empty()){

            auto u = q.front();      //第一个点v出队列
            q.pop();
           if(u.first >= 1 && (Map[u.first-1][u.second] == 0 ||Map[u.first-1][u.second] == 11 || Map[u.first-1][u.second] == 12)  && visited[u.first-1][u.second]== 0){
               //检测向上一格
               pair<int, int> w;
               w.first = u.first-1, w.second = u.second;
               q.push(w);
               visited[u.first-1][u.second] = 1;
               path[u.first-1][u.second] = 3;//到这点要朝上走
               if(Tool[u.first-1][u.second] != 0 || Map[u.first-1][u.second] != 0){//判断是否为目标

                   targetx = u.first-1;
                   targety = u.second;
                   if(Tool[targetx][targety] != 0){
                       staydir = 1;
                   }
                   else{
                       staydir = 0;
                   }
                   break;
               }
            }
            if((Map[u.first+1][u.second] == 0 ||Map[u.first+1][u.second] == 11 || Map[u.first+1][u.second] == 12) && visited[u.first+1][u.second]== 0){
               pair<int, int> w;
               w.first = u.first+1, w.second = u.second;
               q.push(w);
               visited[u.first+1][u.second] = 1;
               path[u.first+1][u.second] = 4;
               if(Tool[u.first+1][u.second] != 0 ||Map[u.first+1][u.second] != 0 ){
                   targetx = u.first+1;
                   targety = u.second;
                   if(Tool[targetx][targety] != 0){
                       staydir = 1;
                   }
                   else{
                       staydir = 0;
                   }
                   break;
               }
            }
            if((Map[u.first][u.second-1] == 0 || Map[u.first][u.second-1] == 11 || Map[u.first][u.second-1] == 12) && visited[u.first][u.second-1]== 0){
               pair<int, int> w;
               w.first = u.first, w.second = u.second-1;
               q.push(w);
               visited[u.first][u.second-1] = 1;
               path[u.first][u.second-1] = 1;
               if(Tool[u.first][u.second-1] != 0 || Map[u.first][u.second-1] != 0){
                   targetx = u.first;
                   targety = u.second - 1;
                   if(Tool[targetx][targety] != 0){
                       staydir = 1;
                   }
                   else{
                       staydir = 0;
                   }
                   break;
               }
            }
            if((Map[u.first][u.second+1] == 0 || Map[u.first][u.second+1] == 11 || Map[u.first][u.second+1] == 12) && visited[u.first][u.second+1]== 0){
               pair<int, int> w;
               w.first = u.first, w.second = u.second+1;
               q.push(w);
               visited[u.first][u.second+1] = 1;
               path[u.first][u.second+1] = 2;
               if(Tool[u.first][u.second+1] != 0 || Map[u.first][u.second+1] != 0){
                   targetx = u.first;
                   targety = u.second + 1;
                   if(Tool[targetx][targety] != 0){
                       staydir = 1;
                   }
                   else{
                       staydir = 0;
                   }
                   break;
               }
            }
        }//while


        int idx = 0;//初始目标方向
        for(int tempi = targetx, tempj = targety;tempi != -1 && tempj != -1;){
            //倒回去找初始朝哪个方向

            if(path[tempi][tempj] == 1){
               tempj++;
               if(path[tempi][tempj] == 0){//找到初始点
                   idx = 1;//找到初始朝向
                   break;
               }
            }
            else if(path[tempi][tempj] == 2){
                tempj--;
                if(path[tempi][tempj] == 0){
                    idx = 2;
                    break;
                }
            }
            else if(path[tempi][tempj] == 3){
                tempi++;
                if(path[tempi][tempj] == 0){
                    idx = 3;
                    break;
                }
            }
            else if(path[tempi][tempj] == 4){
                tempi--;
                if(path[tempi][tempj] == 0){
                    idx = 4;
                    break;
                }
            }

        }

        if(idx == 0){

            srand(time(0));
            int trand = rand()%4;
            for(int t=1;t<=4;t++){

            if(trand == 0 && Map[i-1][j] == 0){
                idx = 3;
            }
            else if(trand == 1 && Map[i+1][j] == 0){
                idx = 4;
            }
            else if(trand == 2 && Map[i][j-1] == 0){
                idx = 1;
            }
            else if (trand == 3 && Map[i][j+1] == 0){
                idx = 2;
            }
            trand = (trand+1)%4;
            }
        }
        return idx;


    }
    else{

       if(Map[i-1][j] == 0){
           return 3;
       }
       else if(Map[i+1][j] == 0){
           return 4;
       }
       else if(Map[i][j-1] == 0){
           return 1;
       }
       else if (Map[i][j+1] == 0){
           return 2;
       }

       else{
           int visited[ROW+5][COL+5] = {0};//标记数组
           queue< pair<int, int> >  q;//队列
           int path[ROW+5][COL+5] = {0};//记录玩家到这个点的上一个方向
           int targetx = -1, targety = -1;//初始目标点
               visited[i][j] = 1;
               pair<int, int> v;
               v.first = i, v.second = j;//对v做已访问标记
               q.push(v);    //顶点v入队列Q
               path[i][j] = 0;
               while(!q.empty()){

                   auto u = q.front();      //第一个点v出队列
                   q.pop();
                  if(u.first >= 1 && (Map[u.first-1][u.second] == 0 ||Map[u.first-1][u.second] == 11 || Map[u.first-1][u.second] == 12 ||Map[u.first-1][u.second] == 77 )  && visited[u.first-1][u.second]== 0){
                      //检测向上一格
                      pair<int, int> w;
                      w.first = u.first-1, w.second = u.second;
                      q.push(w);
                      visited[u.first-1][u.second] = 1;
                      path[u.first-1][u.second] = 3;//到这点要朝上走
                      if(Map[u.first-1][u.second] == 0){//判断是否为目标
                          targetx = u.first-1;
                          targety = u.second;
                          break;
                      }
                   }
                   if((Map[u.first+1][u.second] == 0 ||Map[u.first+1][u.second] == 11 || Map[u.first+1][u.second] == 12 || Map[u.first+1][u.second] == 77) && visited[u.first+1][u.second]== 0){
                      pair<int, int> w;
                      w.first = u.first+1, w.second = u.second;
                      q.push(w);
                      visited[u.first+1][u.second] = 1;
                      path[u.first+1][u.second] = 4;
                      if(Map[u.first+1][u.second] == 0 ){
                          targetx = u.first+1;
                          targety = u.second;
                          break;
                      }
                   }
                   if((Map[u.first][u.second-1] == 0 || Map[u.first][u.second-1] == 11 || Map[u.first][u.second-1] == 12 || Map[u.first][u.second-1] == 77) && visited[u.first][u.second-1]== 0){
                      pair<int, int> w;
                      w.first = u.first, w.second = u.second-1;
                      q.push(w);
                      visited[u.first][u.second-1] = 1;
                      path[u.first][u.second-1] = 1;
                      if(Map[u.first][u.second-1] == 0){
                          targetx = u.first;
                          targety = u.second - 1;
                          break;
                      }
                   }
                   if((Map[u.first][u.second+1] == 0 || Map[u.first][u.second+1] == 11 || Map[u.first][u.second+1] == 12|| Map[u.first][u.second+1] == 77) && visited[u.first][u.second+1]== 0){
                      pair<int, int> w;
                      w.first = u.first, w.second = u.second+1;
                      q.push(w);
                      visited[u.first][u.second+1] = 1;
                      path[u.first][u.second+1] = 2;
                      if( Map[u.first][u.second+1] == 0){
                          targetx = u.first;
                          targety = u.second + 1;
                          break;
                      }
                   }
               }//while

               int idx = 0;//初始目标方向
               for(int tempi = targetx, tempj = targety;tempi != -1 && tempj != -1;){
                   //倒回去找初始朝哪个方向

                   if(path[tempi][tempj] == 1){
                      tempj++;
                      if(path[tempi][tempj] == 0){//找到初始点
                          idx = 1;//找到初始朝向
                          break;
                      }
                   }
                   else if(path[tempi][tempj] == 2){
                       tempj--;
                       if(path[tempi][tempj] == 0){
                           idx = 2;
                           break;
                       }
                   }
                   else if(path[tempi][tempj] == 3){
                       tempi++;
                       if(path[tempi][tempj] == 0){
                           idx = 3;
                           break;
                       }
                   }
                   else if(path[tempi][tempj] == 4){
                       tempi--;
                       if(path[tempi][tempj] == 0){
                           idx = 4;
                           break;
                       }
                   }

               }


              return idx;
       }
    }


}
void AIController ::onUpdate(float deltaTime)
{
    float vx = 0, vy = 0;
    putbomb -= deltaTime;
    if (putbomb <= 0 && (int(transform->x()/40) == int((transform->x()+25)/40) && int(transform->y()/40) == int((transform->y()+35)/40)) )
        {
            putbomb = 9 + (rand()+type)%4;
            int flag = 0;//, flag2 = 0
            auto role = this->gameObject->getComponent<Role>();
            int num = role->getbomb();
            int power = role->getpower();

            for (auto item : transform->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform1 = dynamic_cast<Transform *>(item);
                if (transform1 == nullptr)
                    continue;
                auto gameObject1 = transform1->getParentGameObject();
                auto shooter = gameObject1->getComponent<Shooter>();
                if (shooter != nullptr)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0 && num > 0)
            {


                int tempy = int(transform->y()/40);
                int tempx = int(transform->x()/40);
                Map[tempy][tempx] = 76;
                for(int i = 1;i<= power;i++){
                    if(Map[tempy-i][tempx] == 0){
                    Map[tempy-i][tempx] = 77;
                    }
                    if(Map[tempy+i][tempx] == 0){
                    Map[tempy+i][tempx] = 77;
                    }
                    if(Map[tempy][tempx+i] == 0){
                    Map[tempy][tempx+i] = 77;
                    }
                    if(Map[tempy][tempx-i] == 0){
                    Map[tempy][tempx-i] = 77;
                    }
                }

                int direction = 0;
                direction = searchmap(tempy, tempx);
                if(direction != 0 && staydir == 0){
                staydir = 1;
                this->dir = direction;

                role->changebomb(0);
                auto bomb = new GameObject();
                ImageTransformBuilder()
                    .setPos(transform->pos())
                    .setImage("../project-2-Ericahu118/pictures/23.png")
                    .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                    .addToGameObject(bomb);
                bomb->addComponent(new Shooter(this->gameObject, power, type));
                bomb->addComponent(new Physics());
                attachGameObject(bomb);
                }
                else{
                    Map[tempy][tempx] = 0;
                    for(int i = 1;i<= power;i++){
                        if(Map[tempy-i][tempx] == 77){
                        Map[tempy-i][tempx] = 0;
                        }
                        if(Map[tempy+i][tempx] == 77){
                        Map[tempy+i][tempx] = 0;
                        }
                        if(Map[tempy][tempx+i] == 77){
                        Map[tempy][tempx+i] = 0;
                        }
                        if(Map[tempy][tempx-i] == 77){
                        Map[tempy][tempx-i] = 0;
                        }
                    }
                }
            }
        }
    if (type == 3)
    {

        if (this->dir == 3)
        {

            imagetransform->setImage("../project-2-Ericahu118/pictures/monster1back.png");

            vy = -30;
        }
        else if (this->dir == 4)
        {
            imagetransform->setImage("../project-2-Ericahu118/pictures/monster1.png");
            vy = 30;
        }
        else if (this->dir == 1)
        {
            imagetransform->setImage("../project-2-Ericahu118/pictures/monster1left.png");
            vx = -30;
        }
        else if (this->dir == 2)
        {
            imagetransform->setImage("../project-2-Ericahu118/pictures/monster1right.png");
            //qDebug()<< "here";

            vx = 30;
        }

    }
    else if (type == 4)
    {
        if (this->dir == 3)
        {
            imagetransform->setImage("../project-2-Ericahu118/pictures/monster2back.png");
            vy = -30;
        }
        else if (this->dir == 4)
        {
            imagetransform->setImage("../project-2-Ericahu118/pictures/monster2.png");
            vy = 30;
        }
        else if (this->dir == 1)
        {
            imagetransform->setImage("../project-2-Ericahu118/pictures/monster2left.png");
            vx = -30;
        }
        else if (this->dir == 2)
        {
            imagetransform->setImage("../project-2-Ericahu118/pictures/monster2right.png");
            vx = 30;
        }
    }
    physics->setVelocity(vx, vy);
}
