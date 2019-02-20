#include "aeroplane.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL

Aeroplane::Aeroplane(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rot_x = this->rot_y = this->rot_z = 0;
    this->speedx = this->speedy = this->speedz = this->speedxz = 0;
    int n = 50;
    GLfloat face1[9*n], face2[9*n], body[18*n];
    float angle = ( 2.0*M_PI / float(n));
    float theta = 0.0;
    float length = 3.0;
    float radius1 = 0.5, radius2 = 0.5;
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

    this->object1 = create3DObject(GL_TRIANGLES, 3*n, face1, COLOR_PINK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*n, face2, COLOR_PINK, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6*n, body, COLOR_REALBLACK, GL_FILL);

    theta = 0.0;
    radius1 = 0.5, radius2 = 0.05;
    length = 1.0;

    for(int i=0; i<n; i++){
        face1[9*i] = 0.0f;
        face1[9*i + 1] = 0.0f;
        face1[9*i + 2] = 2.0f - length/2;
        face1[9*i + 3] = radius1*cos(theta);
        face1[9*i + 4] = radius1*sin(theta);
        face1[9*i + 5] = 2.0f - length/2;

        face2[9*i] = 0.0f;
        face2[9*i + 1] = 0.0f;
        face2[9*i + 2] = 2.0f + length/2;
        face2[9*i + 3] = radius2*cos(theta);
        face2[9*i + 4] = radius2*sin(theta);
        face2[9*i + 5] = 2.0f + length/2;

        theta += angle;

        face1[9*i + 6] = radius1*cos(theta);
        face1[9*i + 7] = radius1*sin(theta);
        face1[9*i + 8] = 2.0 - length/2;        

        face2[9*i + 6] = radius2*cos(theta);
        face2[9*i + 7] = radius2*sin(theta);
        face2[9*i + 8] = 2.0f + length/2;

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

    this->object4 = create3DObject(GL_TRIANGLES, 3*n, face1, COLOR_PINK, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 3*n, face2, COLOR_PINK, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 6*n, body, COLOR_PINK, GL_FILL);

    Point a, b, c;
    a.x = 0.5, a.y = 0, a.z = 0.0;
    b.x = 0.5, b.y = 0, b.z = 1.25;
    c.x = 2.5, c.y = 0, c.z = -0.5;

    GLfloat vertex_buffer_data[] = {
        a.x, a.y, a.z,
        b.x, b.y, b.z,
        c.x, c.y, c.z,
    };
    this->lwing = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, COLOR_PINK, GL_FILL);

    a.x = x - 0.5, a.y = 0, a.z = 0.0;
    b.x = x - 0.5, b.y = 0, b.z = 1.25;
    c.x = x - 2.5, c.y = 0, c.z = -0.5;

    GLfloat vertex_buffer_data2[] = {
        a.x, a.y, a.z,
        b.x, b.y, b.z,
        c.x, c.y, c.z
    };
    this->rwing = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_PINK, GL_FILL);

}

void Aeroplane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotatex    = glm::rotate((float) (this->rot_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotatey    = glm::rotate((float) (-this->rot_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotatez    = glm::rotate((float) (this->rot_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centePINK at 0, 0, 0 of cube arouund which we waant to rotate
    // glm::mat4 rotate = glm::translate(glm::vec3(Aeroplane_x, Aeroplane_y, Aeroplane_z)) * rotatey * rotatex * rotatez * glm::translate(glm::vec3(-Aeroplane_x, -Aeroplane_y, -Aeroplane_z));
    
    // Matrices.model *= translate*rotatey;
    Matrices.model *= (translate * rotatex * rotatey * rotatez);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
    draw3DObject(this->lwing);
    draw3DObject(this->rwing);
}

void Aeroplane::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Aeroplane::tick(int no_op) {
    this->speedxz -= 0.01;
    if(this->speedxz < 0.0)
        this->speedxz = 0.0;
    if(this->speedxz > 0.3)
        this->speedxz = 0.3;
    this->speedy -= 0.002;               // Enable gravity.
    if(no_op == 1){
        if(this->rot_z < 0.0)
            this->rot_z += 2.0;
        else if(this->rot_z > 0)
            this->rot_z -= 2.0;
    }
    this->position.x += this->speedxz*(-sin(this->rot_y*(M_PI/180.0)));
    this->position.y += this->speedy;
    this->position.z += this->speedxz*cos(this->rot_y*(M_PI/180.0));
    if(this->position.y < 0.0){
        this->position.y = 0.0;
        this->speedy = 0;
    }
    if(this->position.y > 50){
        this->position.y = 50;
        this->speedy = 0;
    }
    if(this->speedxz > 0 && this->speedy > 0)
        this->speed = sqrt(this->speedy*this->speedy + this->speedxz*this->speedxz);
    else if(this->speedxz > 0)
        this->speed = this->speedxz;
    else if(this->speedy > 0)
        this->speed = this->speedy;
    else
        this->speed = 0;
}

void Aeroplane::forward(){
    this->speedxz += 0.03;
}

void Aeroplane::right(){
    this->rot_z += 2.0;
    if(this->rot_z > 18.0)
        this->rot_z = 18.0;
    this->rot_y += 0.8;
}

void Aeroplane::left(){
    this->rot_z -= 2.0;
    if(this->rot_z < -18.0)
        this->rot_z = -18.0;
    this->rot_y -= 0.8;
}

void Aeroplane::up(){
    if(this->speedy <= 0.06)
        this->speedy += 0.012;
}

void Aeroplane::rot_up(){
    // this->rot_x += 2.0;
}