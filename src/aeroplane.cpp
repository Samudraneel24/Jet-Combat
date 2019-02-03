#include "main.h"
#include "aeroplane.h"

#define GLM_ENABLE_EXPERIMENTAL

Aeroplane::Aeroplane(float x, float y, float z){
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->Body = ThreeD(50, x, y, z, 0.5, 0.5, 3.0, COLOR_RED, COLOR_RED, COLOR_BLACK );
    this->Nose = ThreeD(50, x, y, z + 2.0, 0.5, 0.05, 1.0, COLOR_RED, COLOR_RED, COLOR_RED );
    Point a, b, c;
    a.x = x + 0.5, a.y = y, a.z = 0.0;
    b.x = x + 0.5, b.y = y, b.z = 1.25;
    c.x = x + 2.5, c.y = y, c.z = -0.5;
    this->Leftwing = Triangle(a, b, c, COLOR_RED);
    a.x = x - 0.5, a.y = y, a.z = 0.0;
    b.x = x - 0.5, b.y = y, b.z = 1.25;
    c.x = x - 2.5, c.y = y, c.z = -0.5;
    this->Rightwing = Triangle(a, b, c, COLOR_RED);
}

void Aeroplane::draw(glm::mat4 VP) {
    this->Body.draw(VP);
    this->Nose.draw(VP);
    this->Leftwing.draw(VP);
    this->Rightwing.draw(VP);
}

void Aeroplane::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Aeroplane::tick() {
    this->Body.tick();
    this->Nose.tick();
    this->Leftwing.tick();
    this->Rightwing.tick();
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

