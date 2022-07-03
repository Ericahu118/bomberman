#ifndef ROLE_H
#define ROLE_H
#include <component.h>
class Role : public Component{
    public:
        Role();
        void changehealth(int type);
        void changepower();
        void changebomb(int type);
        void changespeed();
        void changepush();
        void changescore(int score);
        int gethealth();
        int getpower();
        int getbomb();
        int getspeed();
        int getpush();
        int getscore();
    private:
        int health;
        int power;
        int bomb;
        int speed;
        int push;
        int score;

};
extern int cur_role, role1, role2, monster1, monster2;
extern int cur_monster;
extern bool endgame, tostop;

#endif // ROLE_H
