#include "main.h"
#include "ThreeD.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef Fuel_H
#define Fuel_H

class Fuel {
public:
    Fuel() {}
    Fuel(float x, float y, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    float rot_x, rot_y, rot_z;
    float radius, length;
    ThreeD T;
    int n;
private:
    VAO* object;
};

#endif // Fuel_H
