#include "main.h"

#ifndef Arrow_H
#define Arrow_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(Point Checkpoint, Point Plane, float rot_y);
    float rot_x, rot_y, rot_z;
private:
    VAO *object;
};

#endif // Arrow_H
