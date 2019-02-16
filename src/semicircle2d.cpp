#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <fstream>
#include "semicircle2d.h"
#include "main.h"
using namespace std;

Semicircle2d::Semicircle2d(float x, float y, float radius, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->radius = radius;
    const int n = 50;
    static GLfloat vertex_buffer_data[(9*n)/2] ;
    float r = radius;
    float angle = ( 2.0*M_PI / float(n));
    float theta = 0.0;
    for(int i=0;i<n/2;i++){
        vertex_buffer_data[9*i] = 0.0f;
        vertex_buffer_data[9*i + 1] = 0.0f;
        vertex_buffer_data[9*i + 2] = 0.0f;
        vertex_buffer_data[9*i + 3] = r*cos(theta);
        vertex_buffer_data[9*i + 4] = r*sin(theta);
        vertex_buffer_data[9*i + 5] = 0.0f;
        theta += angle;
        if(i == n-1){
            vertex_buffer_data[9*i + 6] = r;
            vertex_buffer_data[9*i + 7] = 0.0f;
            vertex_buffer_data[9*i + 8] = 0.0f;
        }
        else{
            vertex_buffer_data[9*i + 6] = r*cos(theta);
            vertex_buffer_data[9*i + 7] = r*sin(theta);
            vertex_buffer_data[9*i + 8] = 0.0f;
        }
        
    }
    this->object = create3DObject(GL_TRIANGLES, (3*n)/2, vertex_buffer_data, color, GL_FILL);
}

void Semicircle2d::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Semicircle2d::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Semicircle2d::tick() {
    
}

