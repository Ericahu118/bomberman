#include "role.h"
#include <gameobject.h>
int cur_role = 2, cur_monster = 2,role1 = 2, role2 = 1, monster1 = 1, monster2= 1;
bool endgame = false, tostop = false;
Role::Role():Component(){
    health = 1;
    power = 1;
    bomb = 1;
    speed = 1;
    push = 0;
    score = 0;
};

void Role::changebomb(int type){
    if(type==1){
    this->bomb++;
    }
    else{
        this->bomb--;
    }

}
void Role::changespeed(){
    this->speed++;
}
void Role::changepower(){
    this->power++;
}
void Role::changehealth(int type){
    if(type == 1){
    this->health++;
    }
    else{
        this->health--;
    }
}
void Role::changepush(){
    this->push++;
}
void Role::changescore(int score){
    this->score += score;
}
int Role::gethealth(){
    return this->health;
}
int Role::getbomb(){
    return this->bomb;
}
int Role::getpower(){
    return this->power;
}
int Role::getspeed(){
    return this->speed;
}
int Role::getpush(){
    return this->push;
}
int Role::getscore(){
    return this->score;
}
