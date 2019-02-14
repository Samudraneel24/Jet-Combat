#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef Aim_H
#define Aim_H

class Aim {
public:
    Aim() {}
    Aim(int a);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(float posx, float posy, float posz, float rot_y);
	float radius_in, radius_out;
    float rot_x, rot_y, rot_z;
private:
    VAO* ring;
};

#endif // Aim_H
