#ifndef AMMO_H_
#define AMMO_H_

#include <component.h>
#include <gameobject.h>
#include <transform.h>
#include <transformbuilder.h>
class Ammo : public Component {
 public:
  explicit Ammo(QPointF velocity);

  void onAttach() override;
  void onUpdate(float deltaTime) override;
  void findfather(GameObject* father, GameObject*player);
  void changepower(float time);

 protected:
  Transform *transform = nullptr;

  float timeToLive = 1.5;
  QPointF velocity;
  GameObject* father = nullptr;
  GameObject* player = nullptr;
};

#endif  // AMMO_H_
