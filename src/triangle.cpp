#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <fstream>
#include "triangle.h"
#include "main.h"
using namespace std;

Triangle::Triangle(Point a, Point b, Point c,color_t color) {
    this->position = glm::vec3(0, 0, 0);
    GLfloat vertex_buffer_data[] = {
        a.x, a.y, a.z,
        b.x, b.y, b.z,
        c.x, c.y, c.z,
    };
    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color, GL_FILL);
}

void Triangle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (0.0 * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Triangle::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Triangle::tick() {
    // this->position.x -= this->speedx;
}

