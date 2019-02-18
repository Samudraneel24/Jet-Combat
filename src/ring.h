#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef Ring_H
#define Ring_H

class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(float rot_y);
	float radius_in, radius_out;
    float rot_x, rot_y, rot_z;
private:
    VAO* ring;
};

#endif // Ring_H
