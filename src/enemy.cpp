#include "main.h"
#include "enemy.h"

#define GLM_ENABLE_EXPERIMENTAL

Enemy::Enemy(float x, float y, float z){
    this->position = glm::vec3(x, y, z);
    this->Radiusbase = 4.0;
    this->Radiustop = 3.0;
    this->length = 2.0;
    this->Body = ThreeD(25, x, y, z, 4.0, 3.0, 2.0, 0, 0, 0, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    this->Cannon = ThreeD(25, x, y + 1.75, z, 2.0, 1.5, 1.5, 0, 0, 0, COLOR_REALBLACK, COLOR_REALBLACK, COLOR_REALBLACK);
    this->life = 5;
}

void Enemy::draw(glm::mat4 VP) {
    this->Body.draw(VP, 0, 0, 0);
    this->Cannon.draw(VP, 0, 0, 0);
}

void Enemy::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Enemy::tick() {
    this->Body.tick(0, 0, 0, -90, 0, 0);
    this->Cannon.tick(0, 0, 0, -90, 0, 0);
}

