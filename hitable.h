#ifndef HITABLE_H_
#define HITABLE_H_

#include <component.h>

class Hitable : public Component {
 public:
 // Hitable();
   Hitable(int h);
  //virtual void beHit();
  void beHit();
private:
  int health;
};

#endif  // HITABLE_H_
