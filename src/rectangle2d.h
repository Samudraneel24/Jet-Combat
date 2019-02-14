#include "main.h"

#ifndef Rectangle2d_H
#define Rectangle2d_H


class Rectangle2d {
public:
    Rectangle2d() {}
    Rectangle2d(float x, float y, float len, float width, float angle, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float rotation, width, len;
private:
    VAO *object;
};

#endif // Rectangle2d_H
