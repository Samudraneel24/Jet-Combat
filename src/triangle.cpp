#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <fstream>
#include "triangle.h"
#include "main.h"
using namespace std;

Triangle::Triangle(Point origin, Point a, Point b, Point c,color_t color) {
    this->position = glm::vec3(origin.x, origin.y, origin.z);
    this->rot_z = this->rot_x = this->rot_y = 0;
    GLfloat vertex_buffer_data[] = {
        a.x, a.y, a.z,
        b.x, b.y, b.z,
        c.x, c.y, c.z,
    };
    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color, GL_FILL);
}

void Triangle::draw(glm::mat4 VP, float plane_x, float plane_y, float plane_z) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotatex    = glm::rotate((float) (this->rot_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotatey    = glm::rotate((float) (-this->rot_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotatez    = glm::rotate((float) (this->rot_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // glm::mat4 rotate = glm::translate(glm::vec3(plane_x, plane_y, plane_z)) * rotatey * rotatex * rotatez * glm::translate(glm::vec3(-plane_x, -plane_y, -plane_z));
    Matrices.model *= (translate * rotatey * rotatez);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Triangle::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Triangle::tick(float speedx, float speedy, float speedz, float rot_x, float rot_y, float rot_z) {
    this->position.x += speedx;
    this->position.y += speedy;
    this->position.z += speedz;
    this->rot_z = rot_z;
    this->rot_x = rot_x;
    this->rot_y = rot_y;
}
