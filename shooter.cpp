#include "shooter.h"

#include <ammo.h>
#include <gameobject.h>
#include <transform.h>
#include <transformbuilder.h>
#include <gameobject.h>
#include <QGraphicsRectItem>
#include "Obstacle.h"
#include "physics.h"
#include "role.h"
#include "aicontroller.h"
#include"mymap.h"

Shooter::Shooter(GameObject *Player, int time, int type) : Component()
{
    this->player = Player;
    this->time = time;
    this->type = type;
    shootingtime = 0.7 + this->time*1.0;
}
void Shooter::onAttach()
{
    this->transform = this->gameObject->getComponent<Transform>();
    Q_ASSERT(this->transform != nullptr);
}
void Shooter::changestate()
{
    state = 0;

}
int Shooter::getstate()
{
    return state;
}
bool Shooter::checkcondition(){
    if(role1 == 0 && this->type == 1) return true;
    if(role2 == 0 && this->type == 2) return true;
    if(monster1 == 0 && this->type == 3) return true;
    if(monster2 == 0 && this->type == 4) return true;
    else{
        return false;
    }
}
void Shooter::onUpdate(float deltaTime)
{
    int flag = 0;
    for (auto item : this->transform->collidingItems())
    {
        while (item->parentItem() != nullptr)
            item = item->parentItem();
        auto transform1 = dynamic_cast<Transform *>(item);
        if (transform1 == nullptr)
            continue;
        auto gameObject1 = transform1->getParentGameObject();
        if (gameObject1 == this->player && this->gameObject->getComponent<Obstacle>() == nullptr)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0 && this->gameObject->getComponent<Obstacle>() == nullptr)
    {
        this->gameObject->addComponent(new Obstacle());
    } //挡人

    if (cooldown > 0)
    {
        cooldown -= deltaTime;
        if (change == 0)
        {
            this->gameObject->getComponent<ImageTransform>()->setImage("../project-2-Ericahu118/pictures/23.png");
        }
        else if (change == 29)
        {
            this->gameObject->getComponent<ImageTransform>()->setImage("../project-2-Ericahu118/pictures/31.png");
        }
        change = (change + 1) % 60;
        return;
    }
    if (cooldown <= 0)
    {

        if(checkcondition()){
            state = 0;
        }
        if (this->gameObject->getComponent<Physics>() != nullptr)
        {
            this->gameObject->getComponent<Physics>()->setVelocity(0, 0);
        }
        cooldown = 0;

        this->gameObject->getComponent<ImageTransform>()->setImage("../project-2-Ericahu118/pictures/flamecenter.png");
        if (shootingtime < 0)
        {
            if(state == 1&&this->player!=nullptr){
               this->player->getComponent<Role>()->changebomb(1);
                if(this->player->getComponent<AIController>() != nullptr){
                    this->player->getComponent<AIController>()->changestaydir();
                }
            }
            int tempy = int(this->gameObject->getComponent<Transform>()->y()/40);
            int tempx = int(this->gameObject->getComponent<Transform>()->x()/40);
            Map[tempy][tempx] = 0;
            for(int i = 1;i<= this->time;i++){
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
            destory(this->gameObject);
            return;
        }
        else if (this->flag == 1)
        {

            GameObject *ammo1 = new GameObject();
            Ammo *p1 = new Ammo((QPointF(0, -40)));
            p1->findfather(this->gameObject, this->player);
            p1->changepower(this->time * 1.0);
            ammo1->addComponent(p1);
            ImageTransformBuilder()
                .setPos(this->transform->pos())
                .setImage("../project-2-Ericahu118/pictures/flameedge(1).png")
                .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                .addToGameObject(ammo1);
            attachGameObject(ammo1);
            auto ammo2 = new GameObject();
            Ammo *p2 = new Ammo((QPointF(0, 40)));
            p2->findfather(this->gameObject, this->player);
            p2->changepower(this->time * 1.0);
            ammo2->addComponent(p2);
            ImageTransformBuilder()
                .setPos(this->transform->pos())
                .setImage("../project-2-Ericahu118/pictures/flameedge(1).png")
                .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                .addToGameObject(ammo2);
            attachGameObject(ammo2);
            auto ammo3 = new GameObject();
            Ammo *p3 = new Ammo((QPointF(40, 0)));
            p3->findfather(this->gameObject, this->player);
            p3->changepower(this->time * 1.0);
            ammo3->addComponent(p3);
            ImageTransformBuilder()
                .setPos(this->transform->pos())
                .setImage("../project-2-Ericahu118/pictures/flameedge(1).png")
                .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                .addToGameObject(ammo3);
            attachGameObject(ammo3);
            auto ammo4 = new GameObject();
            Ammo *p4 = new Ammo((QPointF(-40, 0)));
            p4->findfather(this->gameObject, this->player);
            p4->changepower(this->time * 1.0);
            ammo4->addComponent(p4);
            ImageTransformBuilder()
                .setPos(this->transform->pos())
                .setImage("../project-2-Ericahu118/pictures/flameedge(1).png")
                .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                .addToGameObject(ammo4);
            attachGameObject(ammo4);
            this->flag = 0;
        }
        shootingtime -= deltaTime;
    }
}
void Shooter::changecooldown()
{
    this->cooldown = 0;
}
