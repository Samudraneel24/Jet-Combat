#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef Triangle_H
#define Triangle_H

class Triangle {
public:
    Triangle() {}
    Triangle(Point a, Point b, Point c, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(float speedx, float speedy, float speedz, float rot_z);
	float speedx, speedy, speedz;
    float rot_x, rot_y, rot_z;
private:
    VAO *object;
};

#endif // Triangle_H
