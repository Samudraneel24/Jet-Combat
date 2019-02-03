#include "main.h"
#include "ThreeD.h"
#include "triangle.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef Aeroplane_H
#define Aeroplane_H

class Aeroplane {
public:
    Aeroplane() {}
    Aeroplane(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    ThreeD Nose;
    ThreeD Body;
    Triangle Leftwing, Rightwing;
private:
    VAO *object;
};

#endif // Aeroplane_H
