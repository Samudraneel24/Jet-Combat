#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <fstream>
#include <algorithm>
#include "altitude.h"
#include "main.h"
#include "sevenseg.h"
using namespace std;

Altitude::Altitude(float x, float y) {
    this->x = x;
    this->y = y;
    this->Character[0] = SevenSeg(this->x, this->y);
    this->Character[1] = SevenSeg(this->x + 0.2, this->y);
    this->Character[2] = SevenSeg(this->x + 0.4, this->y);
    this->Vert = Rectangle2d(x + 0.3, y - 0.7, 1.5, 0.1, -90, COLOR_REALBLACK);
    this->Hor = Rectangle2d(x + 0.2, y - 2.2, 0.3, 0.1, 0, COLOR_REALRED);
}

void Altitude::draw(glm::mat4 VP) {
    this->Character[0].draw(VP, 'a');
    this->Character[1].draw(VP, 'l'); 
    this->Character[2].draw(VP, 't'); 
    this->Vert.draw(VP);
    this->Hor.draw(VP);
}

void Altitude::tick(float altitude) {
    for(int i=0; i < 3; i++)
        this->Character[i].tick();
    this->Vert.tick();
    this->Hor.position.y = (altitude/500.0)*1.5 + this->y - 2.2;
    this->Hor.tick();
}
