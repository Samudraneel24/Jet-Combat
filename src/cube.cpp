#include "cube.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL

Cube::Cube(float x, float y, float z, float speedx, float speedy, float speedz) {
    this->position = glm::vec3(x, y, z);
    this->rot_y = this->rot_z = this->rot_x = 0;
    this->side = 0.5;
    this->speed = 1.5;
    this->speedx = speedx;
    this->speedy = speedy;
    this->speedz = speedz;

    GLfloat cube_data[] = {
        -0.25f,-0.25,-0.25f, // triangle 1 : begin
        -0.25f,-0.25, 0.25f,
        -0.25f, 0.25, 0.25f, // triangle 1 : end
        0.25f, 0.25,-0.25f, // triangle 2 : begin
        -0.25f,-0.25,-0.25f,
        -0.25f, 0.25,-0.25f, // triangle 2 : end
        0.25f,-0.25, 0.25f,
        -0.25f,-0.25,-0.25f,
        0.25f,-0.25,-0.25f,
        0.25f, 0.25,-0.25f,
        0.25f,-0.25,-0.25f,
        -0.25f,-0.25,-0.25f,
        -0.25f,-0.25,-0.25f,
        -0.25f, 0.25, 0.25f,
        -0.25f, 0.25,-0.25f,
        0.25f,-0.25, 0.25f,
        -0.25f,-0.25, 0.25f,
        -0.25f,-0.25,-0.25f,
        -0.25f, 0.25, 0.25f,
        -0.25f,-0.25, 0.25f,
        0.25f,-0.25, 0.25f,
        0.25f, 0.25, 0.25f,
        0.25f,-0.25,-0.25f,
        0.25f, 0.25,-0.25f,
        0.25f,-0.25,-0.25f,
        0.25f, 0.25, 0.25f,
        0.25f,-0.25, 0.25f,
        0.25f, 0.25, 0.25f,
        0.25f, 0.25,-0.25f,
        -0.25f, 0.25,-0.25f,
        0.25f, 0.25, 0.25f,
        -0.25f, 0.25,-0.25f,
        -0.25f, 0.25, 0.25f,
        0.25f, 0.25, 0.25f,
        -0.25f, 0.25, 0.25f,
        0.25f,-0.25, 0.25f
    };

    this->cube = create3DObject(GL_TRIANGLES, 36, cube_data, COLOR_YELLOW, GL_FILL);

}

void Cube::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotatex    = glm::rotate((float) (this->rot_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // glm::mat4 rotatey    = glm::rotate((float) (-this->rot_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // glm::mat4 rotatez    = glm::rotate((float) (this->rot_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // glm::mat4 rotate = glm::translate(glm::vec3(Cube_x, Cube_y, Cube_z)) * rotatey * rotatex * rotatez * glm::translate(glm::vec3(-Cube_x, -Cube_y, -Cube_z));
    
    // Matrices.model *= translate*rotatey;
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->cube);
}

void Cube::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

int Cube::tick() {
    this->position.x += this->speedx;
    this->position.y += this->speedy;
    this->position.z += this->speedz;
    return 0;
}
