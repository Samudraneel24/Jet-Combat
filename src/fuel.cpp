#include "main.h"
#include "fuel.h"

#define GLM_ENABLE_EXPERIMENTAL

Fuel::Fuel(float x, float y, float z){
    this->position = glm::vec3(x, y, z);
    this->radius = 1.5;
    this->length = 3.0;
    this->T = ThreeD(25, x, y, z, 1.5, 1.5, 3.0, 0, 0, 0, COLOR_YELLOW, COLOR_YELLOW, COLOR_REALBLACK);
}

void Fuel::draw(glm::mat4 VP) {
    this->T.draw(VP, 0, 0, 0);
}

void Fuel::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Fuel::tick() {
    this->T.tick(0, 0, 0, 90, 0, 0);
}

