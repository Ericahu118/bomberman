#include "summondummy.h"
#include "mainwindow.h"

#include <gameobject.h>
#include <transform.h>
#include <imagetransform.h>

#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QApplication>


#include "transformbuilder.h"
#include "role.h"

#include <QTimer>


SummonDummy::SummonDummy(GameScene* cur, int type) {
    this->gamescene = cur;
    this->type = type;

}

void SummonDummy::onAttach() {
  auto transform = this->gameObject->getComponent<Transform>();
  Q_ASSERT(transform != nullptr);

  transform->setFiltersChildEvents(true);

}

void SummonDummy::onClick(QGraphicsSceneMouseEvent *ev) {

    if(this->type != -5 && this->type != 5){
        if(this->type == -6){
             QApplication::exit();
        }
    this->type = -this->type;
    }
    else {
       auto curtimer = this->gamescene->getTimer();
       if(type == -5){
           type = 5;
           this->gameObject->getComponent<ImageTransform>()->setImage("../project-2-Ericahu118/pictures/stop(1).png");
           curtimer->stop();

       }
       else if(type == 5){
           type = -5;
           this->gameObject->getComponent<ImageTransform>()->setImage("../project-2-Ericahu118/pictures/start(1).png");
           curtimer->start();
       }
  }

}
void SummonDummy::onUpdate ( float deltaTime ){

    if(tostop){
        auto curtimer = this->gamescene->getTimer();
        curtimer->stop();
    }
    if(endgame){
         endgame = false;

         if(role1 == 1 || role2 == 1){
         auto ending = new GameObject();
         ImageTransformBuilder()
                 .setPos(QPoint(300,100))
                 .setImage("../project-2-Ericahu118/pictures/victory(1).png")
                 .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                 .addToGameObject(ending);
         ending->addComponent(new SummonDummy(this->gamescene, -7));
         attachGameObject(ending);
         }
         else if(monster1 == 1 || monster2 == 1){
              auto ending = new GameObject();
             ImageTransformBuilder()
                     .setPos(QPoint(300,100))
                     .setImage("../project-2-Ericahu118/pictures/lose(1).png")
                     .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                     .addToGameObject(ending);
             ending->addComponent(new SummonDummy(this->gamescene, -7));
             attachGameObject(ending);
         }
          auto backBtn = new GameObject();
          backBtn->setObjectName("backBtn");
          ImageTransformBuilder()
              .setPos(QPointF(410, 450))
              .setImage("../project-2-Ericahu118/pictures/endingbtn.png")
              .setAlignment(Qt::AlignLeft | Qt::AlignTop)
              .addToGameObject(backBtn);
          backBtn->addComponent(new SummonDummy(this->gamescene, -6));
          attachGameObject(backBtn);

          tostop = true;//

         }


    if (type == 1 ){
    type = -type;
    for (auto gameObject : this->gamescene->allgameobject()) {
      destory(gameObject);
    }
    loadScene(this->gamescene);



    return;
    }
    else if(type == 2){
        type = -type;
        if(this->gamescene->getGameObject("menu") == nullptr){
        auto menu = new GameObject();
        menu->setObjectName("menu");
        ImageTransformBuilder()
                .setPos(QPointF(100, 20))
                .setImage("../project-2-Ericahu118/pictures/word(2).png")
                .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                .addToGameObject(menu);
        attachGameObject(menu);
        auto closeBtn = new GameObject();
        closeBtn->setObjectName("closeBtn");
        ImageTransformBuilder()
                .setPos(QPointF(530, 30))
                .setImage("../project-2-Ericahu118/pictures/close(1).png")
                .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                .addToGameObject(closeBtn);
        attachGameObject(closeBtn);
        closeBtn->addComponent(new SummonDummy(this->gamescene, -4));
        }
        return;
    }
    else if(type == 3){
        type = -type;

        destory(this->gameObject);
        QApplication::exit();

    }
    else if(type == 4){
        auto p1 = this->gamescene->getGameObject("menu");
        destory(p1);
        destory(this->gameObject);
    }




}
