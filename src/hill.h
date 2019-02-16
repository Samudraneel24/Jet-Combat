#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef Hill_H
#define Hill_H

class Hill {
public:
    Hill() {}
    Hill(float x, float z, char type);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    int BaseRadius, TopRadius, Height;
    float rot_x, rot_y, rot_z;
    int n;
    char type; 
private:
    VAO * face1;
    VAO * face2;
    VAO * body;
};

#endif // Hill_H
