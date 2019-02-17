#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef Cube_H
#define Cube_H

class Cube {
public:
    Cube() {}
    Cube(float x, float y, float z, float speedx, float speedy, float speedz);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    int tick();
    float speedx, speedy, speedz, speed, side;
    float rot_x, rot_y, rot_z;
private:
    VAO* cube;
};

#endif // Cube_H
