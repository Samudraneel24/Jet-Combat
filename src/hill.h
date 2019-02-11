#include "main.h"
#include "ThreeD.h"
#include "triangle.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef Hill_H
#define Hill_H

class Hill {
public:
    Hill() {}
    Hill(float x, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    ThreeD Base;
    ThreeD Top;
    int BaseRadius, TopBaseRadius, TopTopRadius, Height;
private:
    VAO *object;
};

#endif // Hill_H
