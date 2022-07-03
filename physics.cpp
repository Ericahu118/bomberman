#include"physics.h"
#include "mymap.h"
#include "hitable.h"
#include <cmath>
#include "Obstacle.h"
#include "shooter.h"
#include <component.h>
#include "tool.h"
#include "role.h"
#include "aicontroller.h"
#include "usercontroller.h"



Physics :: Physics ( ) {


}
void Physics :: onAttach ( ) {
transform = this->gameObject->getComponent<Transform >() ;
assert ( transform != nullptr ) ;


}
bool Physics::checkarea(int t)
{


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
        else{
            if(tools == nullptr && obstacle !=nullptr){
                return false;
                break;
            }
        }

    }


    return true;

}
void Physics :: lastpoint(int i, int j){
    last_i = i;
    last_j = j;
}
void Physics :: onUpdate ( float deltaTime ) {
    role = this->gameObject->getComponent<Role>();//fix
    auto ai = this->gameObject->getComponent<AIController>();
    if(ai != nullptr ){
        int speed = role->getspeed();
        if(deltax + deltaTime * vx*speed >=40.0){

            QPoint q((last_j+1)*40, transform->y());
            transform->setPos(q);
            last_j++;
            deltax = 0;

            int tempdir = ai->searchmap(int(transform->y()/40), last_j);

            ai->tochange(tempdir);


        }
        else if(deltax + deltaTime * vx*speed <= -40.0){


            QPoint q((last_j-1)*40, transform->y());
            transform->setPos(q);
            last_j--;
            deltax = 0;

            int tempdir = ai->searchmap(int(transform->y()/40), last_j);

              ai->tochange(tempdir);

        }
        else if(deltay + deltaTime * vy*speed >= 40.0){

            QPoint q(transform->x(), (last_i+1)*40);
            transform->setPos(q);
            last_i++;
            deltay = 0;
            int tempdir = ai->searchmap(last_i, int(transform->x()/40));

            ai->tochange(tempdir);

        }
        else if(deltay + deltaTime * vy*speed <= -40.0){

            QPoint q(transform->x(), (last_i-1)*40);
            transform->setPos(q);
            last_i--;
            deltay = 0;


            int tempdir = ai->searchmap(last_i, int(transform->x()/40));

            ai->tochange(tempdir);

        }
        else{
            deltax += deltaTime * vx*speed ,deltay += deltaTime * vy*speed;
            transform->moveBy( deltaTime * vx*speed , deltaTime * vy*speed );
            if(ai->getdir() == 0){
                int tempdir = ai->searchmap(last_i, last_j);
                ai->tochange(tempdir);
            }
        }
        for (auto item : transform->collidingItems()) {
          while (item->parentItem() != nullptr) item = item->parentItem();
          auto transform1 = dynamic_cast<Transform *>(item);
          if (transform1 == nullptr) continue;
          auto gameObject1 = transform1->getParentGameObject();
          auto obstacle = gameObject1->getComponent<Obstacle>();
          auto physics = gameObject1->getComponent<Physics>();
          auto tools = gameObject1->getComponent<Tools>();
          auto shooter = gameObject1->getComponent<Shooter>();
          if (obstacle == nullptr){
              continue;
          }
          else {
              if(physics!=nullptr && role->getpush() != 0){
                  physics->setVelocity(vx, vy);
              }
              if(tools != nullptr){
                  Tool[int(gameObject1->getComponent<Transform>()->y()/40)][int(gameObject1->getComponent<Transform>()->x()/40)]= 0;
                  role->changescore(50);
                  switch(tools->getType()){
                    case 1:
                      role->changespeed();
                      destory(gameObject1);
                      break;
                    case 2:
                      role->changepush();
                      destory(gameObject1);
                      break;
                     case 3:
                      role->changepower();
                      destory(gameObject1);
                      break;
                     case 4:
                      role->changebomb(1);
                      destory(gameObject1);
                      break;
                     default:
                      break;
                  }
              }

               break;
           }


        }

    }
       else if(this->gameObject->getComponent<UserController>() !=nullptr){
        int speed = role->getspeed();
        transform->moveBy( deltaTime * vx*speed , deltaTime * vy*speed ) ;
        for (auto item : transform->collidingItems()) {
          while (item->parentItem() != nullptr) item = item->parentItem();
          auto transform1 = dynamic_cast<Transform *>(item);
          if (transform1 == nullptr) continue;
          auto gameObject1 = transform1->getParentGameObject();
          auto obstacle = gameObject1->getComponent<Obstacle>();
          auto physics = gameObject1->getComponent<Physics>();
          auto tools = gameObject1->getComponent<Tools>();
          if (obstacle == nullptr){

              continue;
          }
          else {

              if(physics!=nullptr && role->getpush() != 0){
                  physics->setVelocity(vx, vy);
              }
              if(tools != nullptr){
                  role->changescore(50);
                  Tool[int(gameObject1->getComponent<Transform>()->y()/40)][int(gameObject1->getComponent<Transform>()->x()/40)]= 0;
                  switch(tools->getType()){
                    case 1:
                      role->changespeed();
                      destory(gameObject1);
                      break;
                    case 2:
                      role->changepush();
                      destory(gameObject1);
                      break;
                     case 3:
                      role->changepower();
                      destory(gameObject1);
                      break;
                     case 4:
                      role->changebomb(1);
                      destory(gameObject1);
                      break;
                     default:
                      break;
                  }
              }
              transform->moveBy( -deltaTime * vx*speed , -deltaTime * vy*speed ) ;
              break;
           }
        }
        }

       else{
            transform->moveBy( deltaTime * vx , deltaTime * vy ) ;
            for (auto item : transform->collidingItems()) {
              while (item->parentItem() != nullptr) item = item->parentItem();
              auto transform1 = dynamic_cast<Transform *>(item);
              if (transform1 == nullptr) continue;
              auto gameObject1 = transform1->getParentGameObject();
              auto obstacle = gameObject1->getComponent<Obstacle>();

              if (obstacle == nullptr){
                  continue;
              }
              else if(  obstacle != nullptr && (this->vx !=0 || this->vy !=0)){
                transform->moveBy( -deltaTime * vx , -deltaTime * vy ) ;
                this->gameObject->getComponent<Shooter>()->changecooldown();
                break;
               }
        }
     }

}


void Physics :: setVelocity ( float vx , float vy ) {
 this->vx = vx ;
 this->vy = vy ;
}
