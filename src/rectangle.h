#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef Rectangle_H
#define Rectangle_H

class Rectangle {
public:
    Rectangle() {}
    Rectangle(Point a, Point b, Point c, Point d, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
	float speedx, speedy, speedz;
private:
    VAO *object;
};

#endif // Rectangle_H
