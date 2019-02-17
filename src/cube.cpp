#include "parachute.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL

Parachute::Parachute(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rot_y = this->rot_z = this->rot_x = 0;
    this->speedx = this->speedz = 0 = this->speedy = 0;
    this->side = 0.5;

    GLfloat cube_data[] = {
        -0.5f,-0.5,-0.5f, // triangle 1 : begin
        -0.5f,-0.5, 0.5f,
        -0.5f, 0.5, 0.5f, // triangle 1 : end
        0.5f, 0.5,-0.5f, // triangle 2 : begin
        -0.5f,-0.5,-0.5f,
        -0.5f, 0.5,-0.5f, // triangle 2 : end
        0.5f,-0.5, 0.5f,
        -0.5f,-0.5,-0.5f,
        0.5f,-0.5,-0.5f,
        0.5f, 0.5,-0.5f,
        0.5f,-0.5,-0.5f,
        -0.5f,-0.5,-0.5f,
        -0.5f,-0.5,-0.5f,
        -0.5f, 0.5, 0.5f,
        -0.5f, 0.5,-0.5f,
        0.5f,-0.5, 0.5f,
        -0.5f,-0.5, 0.5f,
        -0.5f,-0.5,-0.5f,
        -0.5f, 0.5, 0.5f,
        -0.5f,-0.5, 0.5f,
        0.5f,-0.5, 0.5f,
        0.5f, 0.5, 0.5f,
        0.5f,-0.5,-0.5f,
        0.5f, 0.5,-0.5f,
        0.5f,-0.5,-0.5f,
        0.5f, 0.5, 0.5f,
        0.5f,-0.5, 0.5f,
        0.5f, 0.5, 0.5f,
        0.5f, 0.5,-0.5f,
        -0.5f, 0.5,-0.5f,
        0.5f, 0.5, 0.5f,
        -0.5f, 0.5,-0.5f,
        -0.5f, 0.5, 0.5f,
        0.5f, 0.5, 0.5f,
        -0.5f, 0.5, 0.5f,
        0.5f,-0.5, 0.5f
    };

    this->cube = create3DObject(GL_TRIANGLES, 36, cube_data, COLOR_YELLOW, GL_FILL);

}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
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
    draw3DObject(this->cube);
}

void Parachute::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

int Parachute::tick() {
    // this->position.y += this->speedy;
    // if(this->position.y < 0)
    //     return 1;
    return 0;
}
