#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef ThreeD_H
#define ThreeD_H

class ThreeD {
public:
    ThreeD() {}
    ThreeD(int n, float x, float y, float z, float radius1, float radius2, float length, float rot_x, float rot_y, float rot_z, color_t face1color, color_t face2color, color_t bodycolor);
    glm::vec3 position;
    void draw(glm::mat4 VP, float plane_x, float plane_y, float plane_z);
    void set_position(float x, float y, float z);
    void tick(float speedx, float speedy, float speedz, float rot_x, float rot_y, float rot_z);
	float speed, radius1, radius2, length;
    float rot_x, rot_y, rot_z;
    int n;    
private:
    VAO* object1;
    VAO* object2;
    VAO* object3;
};

#endif // ThreeD_H
