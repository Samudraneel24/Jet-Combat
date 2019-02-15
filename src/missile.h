#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef Missile_H
#define Missile_H

class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z, float rot_y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    float speedx, speedy, speedz, speed;
    float rot_x, rot_y, rot_z;
private:
    VAO* object1;
    VAO* object2;
    VAO* object3;
    VAO* object4;
    VAO* object5;
    VAO* object6;
};

#endif // Missile_H
