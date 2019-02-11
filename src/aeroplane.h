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
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void forward();
    void right();
    ThreeD Nose;
    ThreeD Body;
    Triangle Leftwing, Rightwing;
    float speedx, speedy, speedz;
    float rot_x, rot_y, rot_z;
private:
    VAO *object;
};

#endif // Aeroplane_H
