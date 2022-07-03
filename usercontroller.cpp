#include "usercontroller.h"
#include "shooter.h"
#include "hitable.h"
#include<QDebug>
#include "role.h"
#include"mymap.h"
UserController ::UserController()
{
}
void UserController::setcontroller(int use){
    controller = use;
}
void UserController ::onAttach()
{
    physics = this->gameObject->getComponent<Physics>();
    imagetransform = this->gameObject->getComponent<ImageTransform>();
    transform = this->gameObject->getComponent<Transform>();
    assert(imagetransform != nullptr);
    assert(physics != nullptr);
    assert(transform != nullptr);

}
int UserController:: gettype(){
    return controller;
}
void UserController ::onUpdate(float deltaTime)
{
    if (controller == 1)
    {
        float vx = 0, vy = 0;
        if (getKey(Qt ::Key_A) || (last_dir == 1 &&int(transform->x()/40) != int((transform->x()+25)/40)))
        {
            imagetransform->setImage("../project-2-Ericahu118/pictures/role1left.png");
            vx = -60;
            last_dir = 1;
        }
        else if (getKey(Qt ::Key_D) || (last_dir == 2 && int(transform->x()/40) != int((transform->x()+25)/40)))
        {
            imagetransform->setImage("../project-2-Ericahu118/pictures/role1right.png");
            vx = 60;
            last_dir = 2;
        }
        else if (getKey(Qt ::Key_W) || (last_dir == 3 && int(transform->y()/40) != int((transform->y()+35)/40)))
        {
            imagetransform->setImage("../project-2-Ericahu118/pictures/role1back.png");
            vy = -60;
            last_dir = 3;
        }
        else if (getKey(Qt ::Key_S) || (last_dir == 4 && int(transform->y()/40) != int((transform->y()+35)/40)))
        {
            imagetransform->setImage("../project-2-Ericahu118/pictures/role1.png");
            vy = 60;
            last_dir = 4;
        }


        if(getKey(Qt::Key_Space)){
            int flag = 0;
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
            if(flag == 0 && num > 0){
            role->changebomb(0);
            auto bomb = new GameObject();
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


            ImageTransformBuilder()
                    .setPos(transform->pos())
                    .setImage("../project-2-Ericahu118/pictures/23.png")
                    .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                    .addToGameObject(bomb);
            bomb->addComponent(new Shooter(this->gameObject, power, 1));
            bomb->addComponent(new Physics());
            attachGameObject(bomb);
            }
        }
        physics->setVelocity(vx, vy);
    }
    else if(controller == 2){
        float vx = 0, vy = 0;
        if (getKey(Qt ::Key_J)|| (last_dir == 1 &&int(transform->x()/40) != int((transform->x()+25)/40)))
        {
            imagetransform->setImage("../project-2-Ericahu118/pictures/role2left.png");
            vx = -60;
            last_dir = 1;
        }
        else if (getKey(Qt ::Key_L) || (last_dir == 2 &&int(transform->x()/40) != int((transform->x()+25)/40)))
        {
            imagetransform->setImage("../project-2-Ericahu118/pictures/role2right.png");
            vx = 60;
            last_dir = 2;
        }
        else if (getKey(Qt ::Key_I)|| (last_dir == 3 &&int(transform->y()/40) != int((transform->y()+35)/40)))
        {
            imagetransform->setImage("../project-2-Ericahu118/pictures/role2back.png");
            vy = -60;
            last_dir = 3;
        }
        else if (getKey(Qt ::Key_K) || (last_dir == 4 &&int(transform->y()/40) != int((transform->y()+35)/40)))
        {
            imagetransform->setImage("../project-2-Ericahu118/pictures/role2.png");
            vy = 60;
            last_dir = 4;
        }
        if(getKey(Qt::Key_Return)){

            int flag = 0;
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
            if(flag == 0 && num > 0){
            role->changebomb(0);
            auto bomb = new GameObject();
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



            ImageTransformBuilder()
                    .setPos(transform->pos())
                    .setImage("../project-2-Ericahu118/pictures/23.png")
                    .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                    .addToGameObject(bomb);
            bomb->addComponent(new Shooter(this->gameObject, power, 2));
            bomb->addComponent(new Physics());
            attachGameObject(bomb);
            }
        }
        physics->setVelocity(vx, vy);
    }

}
