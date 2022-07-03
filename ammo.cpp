#include "ammo.h"

#include <QBrush>
#include <QGraphicsEllipseItem>

#include <gamescene.h>
#include "Obstacle.h"
#include "hitable.h"
#include "role.h"
#include "shooter.h"
#include"aicontroller.h"
#include "usercontroller.h"
#include "scoreboard.h"
#include "summondummy.h"
#include"mymap.h"


Ammo::Ammo(QPointF velocity) : Component(), velocity(velocity) {}

void Ammo::onAttach() {
  this->transform = this->gameObject->getComponent<Transform>();
  Q_ASSERT(this->transform != nullptr);


}
void Ammo::findfather(GameObject* father, GameObject*player){
    this->father= father;
    this->player = player;
}
void Ammo::changepower(float time){
    this->timeToLive = time;
}
void Ammo::onUpdate(float deltaTime)
{

    auto shooter = this->father->getComponent<Shooter>();
    timeToLive -= deltaTime;
    this->transform->setPos(this->transform->pos() + velocity * deltaTime);
    if (timeToLive < 0)
    {
        destory(this->gameObject);
     }
    else
    {
        for (auto item : this->transform->collidingItems())
        {
            while (item->parentItem() != nullptr)
                item = item->parentItem();
            auto transform = dynamic_cast<Transform *>(item);
            if (transform == nullptr)
                continue;
            auto gameObject = transform->getParentGameObject();

            auto hitable = gameObject->getComponent<Hitable>();
            auto obstacle = gameObject->getComponent<Obstacle>();
            auto ai = gameObject->getComponent<AIController>();
            auto user = gameObject->getComponent<UserController>();
            if (hitable == nullptr)
            {
                if (obstacle == nullptr || gameObject == this->father)
                {
                    continue;
                }
                else
                {
                    destory(this->gameObject);
                    break;
                }
            }
            else
            {
                if (gameObject == this->player)
                {
                    shooter->changestate();
                    if (ai != nullptr)
                    {
                        cur_monster--;
                        if (ai->gettype() == 3)
                        {
                            monster1 = 0;
                            this->gameObject->gameScene->getGameObject("monster1cast")->getComponent<Scoreboard>()->changepoint();
                        }
                        if (ai->gettype() == 4)
                        {
                            monster2 = 0;
                            this->gameObject->gameScene->getGameObject("monster2cast")->getComponent<Scoreboard>()->changepoint();
                        }
                        if (monster1 == 0 && monster2 == 0)
                        {
                            endgame = true;
                            break;
                        }
                    }
                    else if (user != nullptr)
                    {
                        cur_role--;
                        if (user->gettype() == 1)
                        {
                            role1 = 0;
                            this->gameObject->gameScene->getGameObject("role1cast")->getComponent<Scoreboard>()->changepoint();
                        }
                        else
                        {
                            role2 = 0;
                            this->gameObject->gameScene->getGameObject("role2cast")->getComponent<Scoreboard>()->changepoint();
                        }
                        if (role1 == 0 && role2 == 0)
                        {
                            endgame = true;
                            break;
                        }
                    }
                }
                else if (shooter !=nullptr && shooter->getstate() == 1 && this->player->getComponent<Role>() != nullptr)
                {
                    if (ai != nullptr)
                    {
                        cur_monster--;

                        if (ai->gettype() == 3)
                        {
                            monster1 = 0;

                            this->gameObject->gameScene->getGameObject("monster1cast")->getComponent<Scoreboard>()->changepoint();
                        }
                        else if(ai->gettype() == 4)
                        {
                            monster2 = 0;

                            this->gameObject->gameScene->getGameObject("monster2cast")->getComponent<Scoreboard>()->changepoint();
                        }
                        this->player->getComponent<Role>()->changescore(100);
                        if (monster1 == 0 && monster2 == 0)
                        {
                            endgame = true;
                            break;
                        }
                    }
                    if (user != nullptr)
                    {
                        cur_role--;
                        if (user->gettype() == 1)
                        {
                            role1 = 0;
                            this->gameObject->gameScene->getGameObject("role1cast")->getComponent<Scoreboard>()->changepoint();
                        }
                        else if(user->gettype() == 2)
                        {

                            role2 = 0;
                            this->gameObject->gameScene->getGameObject("role2cast")->getComponent<Scoreboard>()->changepoint();
                        }
                        this->player->getComponent<Role>()->changescore(100);
                        if (role1 == 0 && role2 == 0)
                        {
                            endgame = true;
                            break;
                        }
                    }
                    else
                    {
                        Map[int(gameObject->getComponent<Transform>()->y()/40)][int(gameObject->getComponent<Transform>()->x()/40)]= 0;
                        this->player->getComponent<Role>()->changescore(20);
                    }
                }
                hitable->beHit();
                destory(this->gameObject);
                break;
            }
        }
    }


}


