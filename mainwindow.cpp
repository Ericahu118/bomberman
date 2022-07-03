#include "mainwindow.h"

#include <gameobject.h>
#include <imagetransform.h>
#include <shooter.h>
#include <summondummy.h>
#include <transformbuilder.h>
#include <physics.h>
#include <usercontroller.h>
#include "mymap.h"
#include "hitable.h"
#include "Obstacle.h"
#include "role.h"
#include "tool.h"
#include <QDebug>
#include "scoreboard.h"
#include "aicontroller.h"

#include "./ui_mainwindow.h"

void loadScene(GameScene *gameScene)
{

    createmap();
    GameObject *background = new GameObject();
    GameObject *Player1 = new GameObject();
    GameObject *Player2 = new GameObject();
    GameObject *Monster1 = new GameObject();
    GameObject *Monster2 = new GameObject();
    ImageTransformBuilder()
        .setPos(QPointF(0, 0)) 
        .setImage("../project-2-Ericahu118/pictures/background.png")
        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
        .addToGameObject(background);
    background->getComponent<Transform>()->setOpacity(0.5);
    gameScene->attachGameObject(background);
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            GameObject *block = new GameObject();
            if (i % 2 == 0)
            {
                ImageTransformBuilder()
                    .setPos(QPointF(j * 40, i * 40))
                    .setImage("../project-2-Ericahu118/pictures/1.png")
                    .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                    .addToGameObject(block);
                gameScene->attachGameObject(block);
            }
            if (i % 2 != 0)
            {
                ImageTransformBuilder()
                    .setPos(QPointF(j * 40, i * 40))
                    .setImage("../project-2-Ericahu118/pictures/ground.png")
                    .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                    .addToGameObject(block);
                gameScene->attachGameObject(block);
            }
            if (Tool[i][j] != 0)
            {
                if (Tool[i][j] >= 9)
                {
                    GameObject *tool = new GameObject();
                    tool->addComponent(new Tools(1));
                    tool->addComponent(new Obstacle());
                    ImageTransformBuilder()
                        .setPos(QPointF(j * 40, i * 40))
                        .setImage("../project-2-Ericahu118/pictures/speed.png")
                        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                        .addToGameObject(tool);
                    gameScene->attachGameObject(tool);
                }
                else if (Tool[i][j] >= 7)
                {
                    GameObject *tool = new GameObject();
                    tool->addComponent(new Tools(2));
                    tool->addComponent(new Obstacle());

                    ImageTransformBuilder()
                        .setPos(QPointF(j * 40, i * 40))
                        .setImage("../project-2-Ericahu118/pictures/push.png")
                        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                        .addToGameObject(tool);
                    gameScene->attachGameObject(tool);
                }
                else if (Tool[i][j] >= 5)
                {
                    GameObject *tool = new GameObject();
                    tool->addComponent(new Tools(3));
                    tool->addComponent(new Obstacle());
                    ImageTransformBuilder()
                        .setPos(QPointF(j * 40, i * 40))
                        .setImage("../project-2-Ericahu118/pictures/power.png")
                        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                        .addToGameObject(tool);
                    gameScene->attachGameObject(tool);
                }
                else if (Tool[i][j] >= 1)
                {
                    GameObject *tool = new GameObject();
                    tool->addComponent(new Tools(4));
                    tool->addComponent(new Obstacle());
                    ImageTransformBuilder()
                        .setPos(QPointF(j * 40, i * 40))
                        .setImage("../project-2-Ericahu118/pictures/toolboom.png")
                        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                        .addToGameObject(tool);
                    gameScene->attachGameObject(tool);
                }
            }
        }
    }
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (Map[i][j] == 1 || Map[i][j] == 2 || Map[i][j] == 6)
            {
                GameObject *hardwall = new GameObject();
                hardwall->addComponent(new Obstacle());
                if (Map[i][j] == 1)
                {
                    ImageTransformBuilder()
                        .setPos(QPointF(j * 40, i * 40))
                        .setImage("../project-2-Ericahu118/pictures/grass(1).png")
                        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                        .addToGameObject(hardwall);
                    gameScene->attachGameObject(hardwall);
                }
                else if (Map[i][j] == 2)
                {
                    ImageTransformBuilder()
                        .setPos(QPointF(j * 40, i * 40))
                        .setImage("../project-2-Ericahu118/pictures/monu.png")
                        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                        .addToGameObject(hardwall);
                    gameScene->attachGameObject(hardwall);
                }
                else if (Map[i][j] == 6)
                {
                    ImageTransformBuilder()
                        .setPos(QPointF(j * 40, i * 40))
                        .setImage("../project-2-Ericahu118/pictures/house.png")
                        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                        .addToGameObject(hardwall);
                    gameScene->attachGameObject(hardwall);
                }
            }
            if (Map[i][j] >= 3 && Map[i][j] <= 5)
            {
                GameObject *softwall = new GameObject();
                softwall->addComponent(new Obstacle());
                auto health = Hitable(1);

                softwall->addComponent(new Hitable(1));
                if (Map[i][j] == 4)
                {
                    ImageTransformBuilder()
                        .setPos(QPointF(j * 40, i * 40))
                        .setImage("../project-2-Ericahu118/pictures/block_box.png")
                        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                        .addToGameObject(softwall);
                    gameScene->attachGameObject(softwall);
                }
                else if (Map[i][j] == 3)
                {
                    ImageTransformBuilder()
                        .setPos(QPointF(j * 40, i * 40))
                        .setImage("../project-2-Ericahu118/pictures/tong.png")
                        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                        .addToGameObject(softwall);
                    gameScene->attachGameObject(softwall);
                }
                else if (Map[i][j] == 5)
                {
                    ImageTransformBuilder()
                        .setPos(QPointF(j * 40, i * 40))
                        .setImage("../project-2-Ericahu118/pictures/flower.png")
                        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                        .addToGameObject(softwall);
                    gameScene->attachGameObject(softwall);
                }
            }
            if (Map[i][j] == 11)
            {

                ImageTransformBuilder()
                    .setPos(QPointF(j * 40, i * 40))
                    .setImage("../project-2-Ericahu118/pictures/role1.png")
                    .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                    .addToGameObject(Player1);
                gameScene->attachGameObject(Player1);
                UserController *usecontroller1 = new UserController();
                usecontroller1->setcontroller(1);
                Player1->addComponent(new Physics());
                Player1->addComponent(usecontroller1);
                Player1->addComponent(new Hitable(1));
                //Player1->addComponent(new Obstacle());
                Player1->addComponent(new Role());
                Player1->setObjectName("player1");


            }
            if (Map[i][j] == 12)
            {

                ImageTransformBuilder()
                    .setPos(QPointF(j * 40, i * 40))
                    .setImage("../project-2-Ericahu118/pictures/role2.png")
                    .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                    .addToGameObject(Player2);
                gameScene->attachGameObject(Player2);
                UserController *usecontroller2 = new UserController();
                usecontroller2->setcontroller(2);
                Player2->addComponent(new Physics());
                Player2->addComponent(usecontroller2);
                Player2->addComponent(new Hitable(1));
                //Player2->addComponent(new Obstacle());
                Player2->addComponent(new Role());
                Player2->setObjectName("player2");

            }
            if (Map[i][j] == 21)
            {
                ImageTransformBuilder()
                    .setPos(QPointF(j * 40, i * 40))
                    .setImage("../project-2-Ericahu118/pictures/monster1.png")
                    .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                    .addToGameObject(Monster1);
                gameScene->attachGameObject(Monster1);
                auto physics1 = new Physics();
                physics1->lastpoint(i, j);
                Monster1->addComponent(physics1);
                Monster1->addComponent(new Hitable(1));
                //Monster1->addComponent(new Obstacle());
                Monster1->addComponent(new Role());
                Monster1->addComponent(new AIController(3));
                Monster1->setObjectName("monster1");

            }
            if (Map[i][j] == 22)
            {
                ImageTransformBuilder()
                    .setPos(QPointF(j * 40, i * 40))
                    .setImage("../project-2-Ericahu118/pictures/monster2.png")
                    .setAlignment(Qt::AlignLeft | Qt::AlignTop)
                    .addToGameObject(Monster2);
                gameScene->attachGameObject(Monster2);
                auto physics2 = new Physics();
                physics2->lastpoint(i, j);
                Monster2->addComponent(physics2);
                Monster2->addComponent(new Hitable(1));
                //Monster2->addComponent(new Obstacle());
                Monster2->addComponent(new Role());
                Monster2->addComponent(new AIController(4));
                Monster2->setObjectName("monster2");

            }
        }
    }
    GameObject *rolecast = new GameObject();

    ImageTransformBuilder()
        .setPos(QPointF(800, 100))
        .setImage("../project-2-Ericahu118/pictures/rolecast1.png")
        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
        .addToGameObject(rolecast);
    gameScene->attachGameObject(rolecast);
    rolecast->addComponent(new Scoreboard(Player1));
    rolecast->setObjectName("role1cast");
    GameObject *rolecast2 = new GameObject();

    ImageTransformBuilder()
        .setPos(QPointF(800, 300))
        .setImage("../project-2-Ericahu118/pictures/rolecast2.png")
        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
        .addToGameObject(rolecast2);
    gameScene->attachGameObject(rolecast2);
    rolecast2->addComponent(new Scoreboard(Player2));
    rolecast2->setObjectName("role2cast");
    GameObject *monstercast = new GameObject();

    ImageTransformBuilder()
        .setPos(QPointF(50, 600))
        .setImage("../project-2-Ericahu118/pictures/monstercast1(1).png")
        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
        .addToGameObject(monstercast);
    gameScene->attachGameObject(monstercast);
    monstercast->addComponent(new Scoreboard(Monster1));
    monstercast->setObjectName("monster1cast");
    GameObject *monstercast2 = new GameObject();

    ImageTransformBuilder()
        .setPos(QPointF(350, 600))
        .setImage("../project-2-Ericahu118/pictures/monstercast2(1).png")
        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
        .addToGameObject(monstercast2);
    gameScene->attachGameObject(monstercast2);
    monstercast2->addComponent(new Scoreboard(Monster2));
    monstercast2->setObjectName("monster2cast");
    auto stopBtn = new GameObject();
    stopBtn->setObjectName("stopBtn");
    ImageTransformBuilder()
        .setPos(QPointF(630, 650))
        .setImage("../project-2-Ericahu118/pictures/start(1).png")
        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
        .addToGameObject(stopBtn);
    stopBtn->addComponent(new SummonDummy(gameScene, -5));
    gameScene->attachGameObject(stopBtn);

}

void loadScene1(GameScene *gameScene)
{
    GameObject *beginbackground = new GameObject();
    beginbackground->setObjectName("beginscene");
    ImageTransformBuilder()
        .setPos(QPointF(0, 0))
        .setImage("../project-2-Ericahu118/pictures/enter(1).png")
        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
        .addToGameObject(beginbackground);

    gameScene->attachGameObject(beginbackground);
    GameObject *logo = new GameObject();
    logo->setObjectName("title");
    ImageTransformBuilder()
        .setPos(QPointF(120, 30))
        .setImage("../project-2-Ericahu118/pictures/Title.png")
        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
        .addToGameObject(logo);
    gameScene->attachGameObject(logo);
    auto beginBtn = new GameObject();
    beginBtn->setObjectName("beginBtn");
    ImageTransformBuilder()
        .setPos(QPointF(100, 600))
        .setImage("../project-2-Ericahu118/pictures/beginbtn.png")
        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
        .addToGameObject(beginBtn);
    beginBtn->addComponent(new SummonDummy(gameScene, -1));
    gameScene->attachGameObject(beginBtn);
    auto menuBtn = new GameObject();
    menuBtn->setObjectName("menuBtn");
    ImageTransformBuilder()
        .setPos(QPointF(425, 600))
        .setImage("../project-2-Ericahu118/pictures/menubtn.png")
        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
        .addToGameObject(menuBtn);
    menuBtn->addComponent(new SummonDummy(gameScene, -2));
    gameScene->attachGameObject(menuBtn);
    auto outBtn = new GameObject();
    outBtn->setObjectName("outBtn");
    ImageTransformBuilder()
        .setPos(QPointF(750, 600))
        .setImage("../project-2-Ericahu118/pictures/endbtn.png")
        .setAlignment(Qt::AlignLeft | Qt::AlignTop)
        .addToGameObject(outBtn);
    outBtn->addComponent(new SummonDummy(gameScene, -3));
    gameScene->attachGameObject(outBtn);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameScene = new GameScene();
    this->setFixedSize(1000, 800);
    gameScene->setParent(this);
    auto view = new QGraphicsView(gameScene, this);
    view->setFrameStyle(QFrame::NoFrame);
    view->resize(this->size());
    view->setSceneRect(QRect(0, 0, this->width(), this->height()));
    loadScene1(gameScene);
}

MainWindow::~MainWindow() { delete ui; }
