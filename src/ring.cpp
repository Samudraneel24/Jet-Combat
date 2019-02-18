#include "ring.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL

Ring::Ring(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->radius_in = 6.0;
    this->radius_out = 7.0;
    int n = 50;
    this->rot_x = 0;
    this->rot_y = 0;
    this->rot_z = 0;
    GLfloat Ring[18*n];
    float angle = ( 2.0*M_PI / float(n));
    float theta = 0.0;
    Point cur_in, cur_out, next_in, next_out;
    for(int i=0; i<n; i++){

        cur_in.x = radius_in*cos(theta);
        cur_in.y = radius_in*sin(theta);
        cur_out.x = radius_out*cos(theta);
        cur_out.y = radius_out*sin(theta);

        theta += angle;

        next_in.x = radius_in*cos(theta);
        next_in.y = radius_in*sin(theta);
        next_out.x = radius_out*cos(theta);
        next_out.y = radius_out*sin(theta);

        Ring[18*i] = cur_in.x;
        Ring[18*i + 1] = cur_in.y;
        Ring[18*i + 2] = 0;
        Ring[18*i + 3] = cur_out.x;
        Ring[18*i + 4] = cur_out.y;
        Ring[18*i + 5] = 0;
        Ring[18*i + 6] = next_out.x;
        Ring[18*i + 7] = next_out.y;
        Ring[18*i + 8] = 0;
        Ring[18*i + 9] = cur_in.x;
        Ring[18*i + 10] = cur_in.y;
        Ring[18*i + 11] = 0;
        Ring[18*i + 12] = next_out.x;
        Ring[18*i + 13] = next_out.y;
        Ring[18*i + 14] = 0;
        Ring[18*i + 15] = next_in.x;
        Ring[18*i + 16] = next_in.y;
        Ring[18*i + 17] = 0;
    }

    this->ring = create3DObject(GL_TRIANGLES, 6*n, Ring, color, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotatey    = glm::rotate((float) (-this->rot_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotatey);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ring);
}

void Ring::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ring::tick(float rot_y) {
    this->rot_y = rot_y;
}

