#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <fstream>
#include "arrow.h"
#include "main.h"
using namespace std;

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rot_x = this->rot_y = this->rot_z = 0;
    GLfloat vertex_buffer_data[] = {
      0, 0, 0,        
      -2, 3, 0,
      0, 2, 0,
      0, 0, 0,
      2, 3, 0,
      0, 2, 0,
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rot_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Arrow::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Arrow::tick(Point Checkpoint, Point Plane, float rot_y) {
    this->position.y = Plane.y ;
    float del_x = (Checkpoint.x - Plane.x);
    float del_z = (Checkpoint.z - Plane.z);
    float l = sqrt( del_x*del_x + del_z*del_z);
    if(l > 180){
      this->position.x = Plane.x + (del_x*50.0)/l;
      this->position.z = Plane.z + (del_z*50.0)/l;
    }
    else{
      this->position.x = Checkpoint.x;
      this->position.y = Checkpoint.y + 8;
      this->position.z = Checkpoint.z;
    }
    this->rot_y = -rot_y;
}
