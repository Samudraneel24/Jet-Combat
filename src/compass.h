#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef Compass_H
#define Compass_H

class Compass {
public:
    Compass() {}
    Compass(float x, float y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(float rot_y);
    float rot_z;
private:
    VAO* object1;
    VAO* object2;
    VAO* object3;
    VAO* object4;
};

#endif // Compass_H
