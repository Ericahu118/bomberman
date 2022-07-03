#include "scoreboard.h"
#include <gameobject.h>
#include <transform.h>
#include <imagetransform.h>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QTimer>
#include "role.h"
#include <QFont>

Scoreboard ::Scoreboard(GameObject * gameobject){
    this->player = gameobject;
}

void Scoreboard :: onAttach(){
    auto transform = this->gameObject->getComponent<Transform>();
     Q_ASSERT(transform != nullptr);
    for(int i = 0;i<6;i++){
    this->text[i] = new QGraphicsSimpleTextItem(transform);
    text[i]->setText("0");
    text[i]->setPos(150, 27+16*i);
    QFont ft;
    ft.setPointSize(10);
    ft.setBold(true);
    text[i]->setFont(ft);
    }
    text[0]->setText("Live!");
    text[4]->setText("No");
    QFont ft2;
    ft2.setPointSize(8);
    ft2.setBold(true);
    text[5]->setFont(ft2);
    text[5]->setPos(49,31+16*4);
}
void Scoreboard:: changepoint(){
    this->player = nullptr;
}
void Scoreboard::onUpdate(float deltaTime){
    if(this->player != nullptr){
    auto role = this->player->getComponent<Role>();
    if(role != nullptr){
    text[0]->setText("Live!");
    text[1]->setText(QString::number(role->getspeed()*40));
    text[2]->setText(QString::number(role->getbomb()));
    text[3]->setText(QString::number(role->getpower()));
    text[5]->setText(QString::number(role->getscore()));
    if(role->getpush() != 0){
         text[4]->setText("Yes");
    }
    }
    else{
       text[0]->setText("Die!");
    }
    }
    else{
        text[0]->setText("Die!");
    }

}
