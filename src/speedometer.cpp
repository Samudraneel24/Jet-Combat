#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <fstream>
#include <algorithm>
#include "speedometer.h"
#include "main.h"
#include "sevenseg.h"
using namespace std;

Speedometer::Speedometer(float x, float y) {
    this->x = x;
    this->y = y;
    this->Character[0] = SevenSeg(this->x, this->y);
    this->Character[1] = SevenSeg(this->x + 0.2, this->y);
    this->Character[2] = SevenSeg(this->x + 0.4, this->y);
    this->Character[3] = SevenSeg(this->x + 0.6, this->y);
    this->Character[4] = SevenSeg(this->x + 0.8, this->y);
    this->Out = Semicircle2d(this->x + 0.5, this->y + 0.3, 0.9, COLOR_REALRED);
    this->In = Semicircle2d(this->x + 0.5, this->y + 0.3, 0.8, COLOR_REALBLACK);
    Point a, b, c, origin;
    origin.x = this->x + 0.5;
    origin.y = this->y + 0.4;
    origin.z = 0;
    a.x = -0.7, a.y = 0, a.z = 0;
    b.x = 0, b.y = 0.1, b.z = 0;
    c.x = 0, c.y = -0.1, c.z = 0;
    this->T = Triangle(origin, a, b, c, COLOR_GREY);
}

void Speedometer::draw(glm::mat4 VP) {
    this->Character[0].draw(VP, 's');
    this->Character[1].draw(VP, 'p'); 
    this->Character[2].draw(VP, 'e'); 
    this->Character[3].draw(VP, 'e'); 
    this->Character[4].draw(VP, 'd'); 
    this->Out.draw(VP);
    this->In.draw(VP);
    this->T.draw(VP, 0, 0, 0);
}

void Speedometer::tick(float speed) {
    for(int i=0; i < 5; i++)
        this->Character[i].tick();
    this->Out.tick();
    float rot = -(speed/0.3)*180.0;
    this->In.tick();
    this->T.tick(0, 0, 0, 0, 0, rot);
}
