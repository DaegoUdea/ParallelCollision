#include "rect_collision.h"

RectCollision::RectCollision() {

}

RectCollision::~RectCollision() {

}

bool RectCollision::check_collision(GameObject* object1, GameObject* object2) {
  float left1, right1, top1, bottom1;
  float left2, right2, top2, bottom2;

  left1 = object1->getPosition()->getX();
  right1 = object1->getPosition()->getX() + object1->getWidth();
  top1 = object1->getPosition()->getY();
  bottom1 = object1->getPosition()->getY() + object1->getHeight();

  left2 = object2->getPosition()->getX();
  right2 = object2->getPosition()->getX() + object2->getWidth();
  top2 = object2->getPosition()->getY();
  bottom2 = object2->getPosition()->getY() + object2->getHeight();

  if ( left1 > right2 ) {
    return false; // No collision
  }

  if ( right1 < left2 ) {
    return false;
  }

  if ( top1 > bottom2 ) {
    return false;
  }

  if ( bottom1 < top2 ) {
    return false;
  }

  return true;
}
