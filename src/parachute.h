#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef Parachute_H
#define Parachute_H

class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    int tick();
    float speedx, speedy, speedz;
    float rot_x, rot_y, rot_z;
private:
    VAO* top;
    VAO* string;
    VAO* cube;
};

#endif // Parachute_H
