#include "ThreeD.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL

ThreeD::ThreeD(int n, float x, float y, float z, float radius1, float radius2, float length, color_t face1color, color_t face2color,color_t bodycolor) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->radius1 = radius1;
    this->radius2 = radius2;
    this->length = length;
    this->n = n;
    // this->rotation = 90.0;
    speed = 1;
    GLfloat face1[9*n], face2[9*n], body[18*n];
    float angle = ( 2.0*M_PI / float(n));
    float theta = 0.0;
    for(int i=0; i<n; i++){
        face1[9*i] = 0.0f;
        face1[9*i + 1] = 0.0f;
        face1[9*i + 2] = 0.0f - length/2;
        face1[9*i + 3] = radius1*cos(theta);
        face1[9*i + 4] = radius1*sin(theta);
        face1[9*i + 5] = 0.0f - length/2;

        face2[9*i] = 0.0f;
        face2[9*i + 1] = 0.0f;
        face2[9*i + 2] = 0.0f + length/2;
        face2[9*i + 3] = radius2*cos(theta);
        face2[9*i + 4] = radius2*sin(theta);
        face2[9*i + 5] = 0.0f + length/2;

        theta += angle;

        face1[9*i + 6] = radius1*cos(theta);
        face1[9*i + 7] = radius1*sin(theta);
        face1[9*i + 8] = 0.0 - length/2;        

        face2[9*i + 6] = radius2*cos(theta);
        face2[9*i + 7] = radius2*sin(theta);
        face2[9*i + 8] = 0.0f + length/2;

        body[18*i] = face1[9*i + 3];
        body[18*i + 1] = face1[9*i + 4];
        body[18*i + 2] = face1[9*i + 5];
        body[18*i + 3] = face1[9*i + 6];
        body[18*i + 4] = face1[9*i + 7];
        body[18*i + 5] = face1[9*i + 8];
        body[18*i + 6] = face2[9*i + 3];
        body[18*i + 7] = face2[9*i + 4];
        body[18*i + 8] = face2[9*i + 5];

        body[18*i + 9] = face1[9*i + 6];
        body[18*i + 10] = face1[9*i + 7];
        body[18*i + 11] = face1[9*i + 8];
        body[18*i + 12] = face2[9*i + 6];
        body[18*i + 13] = face2[9*i + 7];
        body[18*i + 14] = face2[9*i + 8];
        body[18*i + 15] = face2[9*i + 3];
        body[18*i + 16] = face2[9*i + 4];
        body[18*i + 17] = face2[9*i + 5];

    }

    this->object1 = create3DObject(GL_TRIANGLES, 3*n, face1, face1color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*n, face2, face2color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6*n, body, bodycolor, GL_FILL);
}

void ThreeD::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void ThreeD::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void ThreeD::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

