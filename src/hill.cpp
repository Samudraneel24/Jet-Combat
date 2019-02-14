#include "main.h"
#include "hill.h"

#define GLM_ENABLE_EXPERIMENTAL

Hill::Hill(float x, float z){
    this->position = glm::vec3(x, 0, z);
    this->rot_x = -90;
    this->rot_y = this->rot_z = 0;
    this->BaseRadius = 15 + rand()%10;
    this->TopRadius = rand()%(this->BaseRadius/2);
    this->Height = (this->BaseRadius - this->TopRadius) - (this->TopRadius+1) + rand()%(2*this->TopRadius + 2);
    int n = 15;
    this->n = n;
    float radius1 = this->BaseRadius;
    float radius2 = this->TopRadius;
    float length = this->Height;

    GLfloat face1[9*n], face2[9*n], body[18*n], face1_color[9*n], face2_color[9*n], body_color[18*n];
    float angle = ( 2.0*M_PI / float(n));
    float theta = 0.0;
    float r, g, b, HI, LO;
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


        for(int j = 0; j<3; j++){
            HI = 0.3, LO = 0.0;
            r = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
            b = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
            LO = 0.7, HI = 1.0;
            g = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
            face1_color[9*i + 3*j] = r;
            face1_color[9*i + 3*j + 1] = g; 
            face1_color[9*i + 3*j + 2] = b; 
        }

        for(int j = 0; j<3; j++){
            HI = 0.4, LO = 0.0;
            r = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
            b = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
            LO = 0.7, HI = 1.0;
            g = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
            face2_color[9*i + 3*j] = r;
            face2_color[9*i + 3*j + 1] = g; 
            face2_color[9*i + 3*j + 2] = b; 
        }

        body_color[18*i] = face1_color[9*i + 3];
        body_color[18*i + 1] = face1_color[9*i + 4];
        body_color[18*i + 2] = face1_color[9*i + 5];
        body_color[18*i + 3] = face1_color[9*i + 6];
        body_color[18*i + 4] = face1_color[9*i + 7];
        body_color[18*i + 5] = face1_color[9*i + 8];
        body_color[18*i + 6] = face2_color[9*i + 3];
        body_color[18*i + 7] = face2_color[9*i + 4];
        body_color[18*i + 8] = face2_color[9*i + 5];

        body_color[18*i + 9] = face1_color[9*i + 6];
        body_color[18*i + 10] = face1_color[9*i + 7];
        body_color[18*i + 11] = face1_color[9*i + 8];
        body_color[18*i + 12] = face2_color[9*i + 6];
        body_color[18*i + 13] = face2_color[9*i + 7];
        body_color[18*i + 14] = face2_color[9*i + 8];
        body_color[18*i + 15] = face2_color[9*i + 3];
        body_color[18*i + 16] = face2_color[9*i + 4];
        body_color[18*i + 17] = face2_color[9*i + 5];

    }

    this->face1 = create3DObject(GL_TRIANGLES, 3*n, face1, face1_color, GL_FILL);
    this->face2 = create3DObject(GL_TRIANGLES, 3*n, face2, face2_color, GL_FILL);
    this->body = create3DObject(GL_TRIANGLES, 6*n, body, body_color, GL_FILL);

    // this->Base = ThreeD(50, x, 0, z, this->BaseRadius, this->BaseRadius, 0.2, 90, 0, 0, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN);
    // this->Top = ThreeD(50, x, 0.0, z, this->TopTopRadius, this->TopBaseRadius, this->Height, 90, 0, 0, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN);
}

void Hill::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotatex    = glm::rotate((float) (this->rot_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotatey    = glm::rotate((float) (-this->rot_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotatez    = glm::rotate((float) (this->rot_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    glm::mat4 rotate = rotatey * rotatex * rotatez;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->face1);
    draw3DObject(this->face2);
    draw3DObject(this->body);
}

void Hill::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Hill::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

