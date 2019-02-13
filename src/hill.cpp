#include "main.h"
#include "hill.h"

#define GLM_ENABLE_EXPERIMENTAL

Hill::Hill(float x, float z){
    this->position = glm::vec3(x, 0, z);
    this->rotation = 0;
    this->BaseRadius = 6 + rand()%9;
    this->TopBaseRadius = 6 + rand()%( max(1, this->BaseRadius - 6) );
    this->TopTopRadius = rand()%( max(1, this->TopBaseRadius/2 - 1 ) );
    this->Height = 1 + rand()%( max(1, this->TopBaseRadius - this->TopTopRadius - 1) );
    this->Base = ThreeD(50, x, 0, z, this->BaseRadius, this->BaseRadius, 0.2, 90, 0, 0, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN);
    this->Top = ThreeD(50, x, 0.0, z, this->TopTopRadius, this->TopBaseRadius, this->Height, 90, 0, 0, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN);
}

void Hill::draw(glm::mat4 VP) {
    this->Base.draw(VP, 0, 0, 0);
    this->Top.draw(VP, 0, 0, 0);
}

void Hill::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Hill::tick() {
    this->Base.tick(0, 0, 0, 90, 0, 0);
    this->Top.tick(0, 0, 0, 90, 0, 0);
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

