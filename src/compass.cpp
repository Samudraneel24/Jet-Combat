#include "compass.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL

Compass::Compass(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    int n = 50;
    GLfloat Circle_out[9*n], Circle_in[9*n];
    float angle = ( 2.0*M_PI / float(n));
    float theta = 0.0;
    float radius1 = 0.6, radius2 = 0.8;
    for(int i=0; i<n; i++){
        Circle_in[9*i] = 0.0f;
        Circle_in[9*i + 1] = 0.0f;
        Circle_in[9*i + 2] = 0.0f;
        Circle_in[9*i + 3] = radius1*cos(theta);
        Circle_in[9*i + 4] = radius1*sin(theta);
        Circle_in[9*i + 5] = 0.0f;

        Circle_out[9*i] = 0.0f;
        Circle_out[9*i + 1] = 0.0f;
        Circle_out[9*i + 2] = 0.0f;
        Circle_out[9*i + 3] = radius2*cos(theta);
        Circle_out[9*i + 4] = radius2*sin(theta);
        Circle_out[9*i + 5] = 0.0f;

        theta += angle;

        Circle_in[9*i + 6] = radius1*cos(theta);
        Circle_in[9*i + 7] = radius1*sin(theta);
        Circle_in[9*i + 8] = 0.0;        

        Circle_out[9*i + 6] = radius2*cos(theta);
        Circle_out[9*i + 7] = radius2*sin(theta);
        Circle_out[9*i + 8] = 0.0f;
    }

    GLfloat Up[] = {
        0, 0.45, 0,
        -0.1, 0, 0,
        0.1, 0, 0,
    };

    GLfloat Down[] = {
        0, -0.45, 0,
        -0.1, 0, 0,
        0.1, 0, 0,
    };

    this->object1 = create3DObject(GL_TRIANGLES, 3*n, Circle_out, COLOR_REALBLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*n, Circle_in, COLOR_GREY, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 3, Up, COLOR_REALRED, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 3, Down, COLOR_REALBLACK, GL_FILL);

}

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotatez    = glm::rotate((float) (this->rot_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotatez);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Compass::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Compass::tick(float rot_y) {
    this->rot_z = rot_y;
}

