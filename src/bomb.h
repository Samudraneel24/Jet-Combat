#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef Bomb_H
#define Bomb_H

class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z, float speed, float speedy, float rot_y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    int tick();
    float speedx, speedy, speedz, speed;
    float rot_x, rot_y, rot_z;
private:
    VAO* object1;
    VAO* object2;
    VAO* object3;
};

#endif // Bomb_H







