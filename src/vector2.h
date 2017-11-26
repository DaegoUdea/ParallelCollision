#ifndef SRC_VECTOR2_H_
#define SRC_VECTOR2_H_

class Vector2 {
public:
  Vector2();
  Vector2(int x, int y);

  static Vector2* lerp(Vector2* from, Vector2* to, float percent);
  static void add(Vector2* vector1, Vector2* vector2, Vector2* out);
  static void substract(Vector2* vector1, Vector2* vector2, Vector2* out);
  static void dot(Vector2* vector1, Vector2* vector2, float* scalar);

  // Setters
  void setX(float new_x);
  void setY(float new_y);

  // Getters
  float getX();
  float getY();

private:
  float x;
  float y;
};

#endif // SRC_VECTOR2_H_
