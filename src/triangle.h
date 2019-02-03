#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef Triangle_H
#define Triangle_H

class Triangle {
public:
    Triangle() {}
    Triangle(Point a, Point b, Point c, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
	float speedx, speedy, speedz;
private:
    VAO *object;
};

#endif // Triangle_H
