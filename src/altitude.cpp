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
    this->Character[1] = SevenSeg(this->x + 0.3, this->y);
    this->Character[2] = SevenSeg(this->x + 0.6, this->y);
    this->Character[3] = SevenSeg(this->x + 0.9, this->y);
    this->Character[4] = SevenSeg(this->x + 1.2, this->y);
    this->Character[5] = SevenSeg(this->x + 1.5, this->y);
    this->Character[6] = SevenSeg(this->x + 1.8, this->y);
    this->Character[7] = SevenSeg(this->x + 2.1, this->y);
    this->Character[8] = SevenSeg(this->x + 2.4, this->y);
}

void Altitude::draw(glm::mat4 VP, int Altitude) {
    int dig;
    char c[5];
    for(int i=0; i<5; i++){
        dig = Altitude%10;
        c[i] = dig + '0';
        Altitude/=10;
    }
    this->Character[0].draw(VP, 'a');
    this->Character[1].draw(VP, 'l'); 
    this->Character[2].draw(VP, 't'); 
    this->Character[3].draw(VP, '-'); 
    this->Character[4].draw(VP, c[4]); 
    this->Character[5].draw(VP, c[3]); 
    this->Character[6].draw(VP, c[2]); 
    this->Character[7].draw(VP, c[1]); 
    this->Character[8].draw(VP, c[0]); 
}

void Altitude::tick() {
    for(int i=0; i < 9; i++)
        this->Character[i].tick();
}
