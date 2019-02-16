#include "main.h"

#ifndef Semicircle2d_H
#define Semicircle2d_H


class Semicircle2d {
public:
    Semicircle2d() {}
    Semicircle2d(float x, float y, float radius, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float radius;
private:
    VAO *object;
};

#endif // Semicircle2d_H
