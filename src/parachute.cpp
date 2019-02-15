#include "parachute.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL

Parachute::Parachute(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rot_y = this->rot_z = 0;
    this->rot_x = 90;
    this->speedx = this->speedz = 0;
    this->speedy = -0.15;
    int n = 50;
    GLfloat top_data[9*n], string_data[9*n], color_data[9*n];
    float angle = ( 2.0*M_PI / float(n));
    float theta = 0.0;
    float length = 1.5;
    float radius = 2.0;
    Point up, down;
    up.x = up.z = down.x = down.z = 0;
    up.y = 2.0;
    down.y = -2.0;
    for(int i=0; i<n; i++){
        top_data[9*i] = up.x;
        top_data[9*i + 1] = up.y;
        top_data[9*i + 2] = up.z;
        top_data[9*i + 3] = radius*cos(theta);
        top_data[9*i + 4] = 0;
        top_data[9*i + 5] = radius*sin(theta);
        theta += angle;
        top_data[9*i + 6] = radius*cos(theta);
        top_data[9*i + 7] = 0;
        top_data[9*i + 8] = radius*sin(theta);

        color_data[9*i] = 0;
        color_data[9*i + 1] = 0;
        color_data[9*i + 2] = 255;

        if(i%2 == 0){
            color_data[9*i] = 0;
            color_data[9*i + 1] = 255;
            color_data[9*i + 2] = 0;
        }
        else{
            color_data[9*i] = 255;
            color_data[9*i + 1] = 0;
            color_data[9*i + 2] = 0;
        }
    }

    int n2 = 6;
    theta = 0;
    angle =  ( 2.0*M_PI / float(n2));

    for(int i=0; i<n2; i++){
        string_data[9*i] = down.x;
        string_data[9*i + 1] = down.y;
        string_data[9*i + 2] = down.z;
        string_data[9*i + 3] = radius*cos(theta);
        string_data[9*i + 4] = 0;
        string_data[9*i + 5] = radius*sin(theta);
        theta += angle;
        string_data[9*i + 6] = radius*cos(theta);
        string_data[9*i + 7] = 0;
        string_data[9*i + 8] = radius*sin(theta);
    }

    GLfloat cube_data[] = {
        -1.0f,-1.0f - 3,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f - 3, 1.0f,
        -1.0f, 1.0f - 3, 1.0f, // triangle 1 : end
        1.0f, 1.0f - 3,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f - 3,-1.0f,
        -1.0f, 1.0f - 3,-1.0f, // triangle 2 : end
        1.0f,-1.0f - 3, 1.0f,
        -1.0f,-1.0f - 3,-1.0f,
        1.0f,-1.0f - 3,-1.0f,
        1.0f, 1.0f - 3,-1.0f,
        1.0f,-1.0f - 3,-1.0f,
        -1.0f,-1.0f - 3,-1.0f,
        -1.0f,-1.0f - 3,-1.0f,
        -1.0f, 1.0f - 3, 1.0f,
        -1.0f, 1.0f - 3,-1.0f,
        1.0f,-1.0f - 3, 1.0f,
        -1.0f,-1.0f - 3, 1.0f,
        -1.0f,-1.0f - 3,-1.0f,
        -1.0f, 1.0f - 3, 1.0f,
        -1.0f,-1.0f - 3, 1.0f,
        1.0f,-1.0f - 3, 1.0f,
        1.0f, 1.0f - 3, 1.0f,
        1.0f,-1.0f - 3,-1.0f,
        1.0f, 1.0f - 3,-1.0f,
        1.0f,-1.0f - 3,-1.0f,
        1.0f, 1.0f - 3, 1.0f,
        1.0f,-1.0f - 3, 1.0f,
        1.0f, 1.0f - 3, 1.0f,
        1.0f, 1.0f - 3,-1.0f,
        -1.0f, 1.0f - 3,-1.0f,
        1.0f, 1.0f - 3, 1.0f,
        -1.0f, 1.0f - 3,-1.0f,
        -1.0f, 1.0f - 3, 1.0f,
        1.0f, 1.0f - 3, 1.0f,
        -1.0f, 1.0f - 3, 1.0f,
        1.0f,-1.0f - 3, 1.0f
    };

    this->top = create3DObject(GL_TRIANGLES, 3*n, top_data, color_data, GL_FILL);
    this->string = create3DObject(GL_LINES, 3*n2, string_data, COLOR_REALBLACK, GL_FILL);
    this->cube = create3DObject(GL_TRIANGLES, 36, cube_data, COLOR_YELLOW, GL_FILL);

}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotatex    = glm::rotate((float) (this->rot_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // glm::mat4 rotatey    = glm::rotate((float) (-this->rot_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // glm::mat4 rotatez    = glm::rotate((float) (this->rot_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // glm::mat4 rotate = glm::translate(glm::vec3(Parachute_x, Parachute_y, Parachute_z)) * rotatey * rotatex * rotatez * glm::translate(glm::vec3(-Parachute_x, -Parachute_y, -Parachute_z));
    
    // Matrices.model *= translate*rotatey;
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->top);
    draw3DObject(this->string);
    draw3DObject(this->cube);
}

void Parachute::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

int Parachute::tick() {
    this->position.y += this->speedy;
    if(this->position.y < 0)
        return 1;
    return 0;
}
