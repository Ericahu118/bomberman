#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include<component.h>
#include <gamescene.h>
#include <QGraphicsSimpleTextItem>

class Scoreboard : public Component{
    public:
        Scoreboard(GameObject* gameobject);

        void onAttach() override;

        void onUpdate(float deltaTime) override;

        void changepoint();
    private:
        GameObject * player;
        QGraphicsSimpleTextItem * text[6];


};

#endif // SCOREBOARD_H
