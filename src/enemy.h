#include "main.h"
#include "ThreeD.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef Enemy_H
#define Enemy_H

class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    float rot_x, rot_y, rot_z;
    float Radiustop, Radiusbase, length;
    ThreeD Body, Cannon;
    int life;
private:
    VAO* object;
};

#endif // Enemy_H
