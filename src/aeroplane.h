#include "main.h"

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
    void tick(int no_op);
    void forward();
    void right();
    void left();
    float speedx, speedy, speedz;
    float rot_x, rot_y, rot_z;
private:
    VAO* object1;
    VAO* object2;
    VAO* object3;
    VAO* lwing;
    VAO* rwing;
    VAO* object4;
    VAO* object5;
    VAO* object6;
};

#endif // Aeroplane_H
