#include "hitable.h"
#include "role.h"
#include <gameobject.h>
Hitable::Hitable(int h):Component() {
    this->health = h;

}

void Hitable::beHit() {

    this->health--;
    if(this->health <= 0){
    destory(this->gameObject);
    }
}
