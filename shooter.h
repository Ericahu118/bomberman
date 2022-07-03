#ifndef SHOOTER_H_
#define SHOOTER_H_

#include "component.h"
#include <gameobject.h>
class Transform;

class Shooter : public Component {
 public:
  Shooter(GameObject* Player, int time, int type);

  void onAttach() override;
  void onUpdate(float deltaTime) override;
  void changecooldown();
  void changestate();
  int getstate();
  bool checkcondition();


 protected:
  Transform *transform = nullptr;
  GameObject* player = nullptr;
  //const float interval = 5;
  float cooldown = 4;
  float shootingtime = 1;
  int time;
  int change = 0;
  int state = 1;
  int type = 0;
  int flag = 1;//put fire

};

#endif  // SHOOTER_H_
