#ifndef SUMMONDUMMY_H_
#define SUMMONDUMMY_H_

#include <component.h>
#include <gamescene.h>

class SummonDummy : public Component {
 public:
  SummonDummy(GameScene* cur, int type);

  void onAttach() override;

  void onClick(QGraphicsSceneMouseEvent *ev) override;

  void onUpdate ( float deltaTime ) override;
private:
  GameScene * gamescene;
  int type;

};

#endif  // SUMMONDUMMY_H_
