#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL
#ifndef ThreeD_H
#define ThreeD_H

class ThreeD {
public:
    ThreeD() {}
    ThreeD(int n, float x, float y, float z, float radius1, float radius2, float length, color_t face1color, color_t face2color, color_t bodycolor);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
	float speed, radius1, radius2, length;
    int n;    
private:
    VAO *object1;
    VAO* object2;
    VAO* object3;
};

#endif // ThreeD_H
