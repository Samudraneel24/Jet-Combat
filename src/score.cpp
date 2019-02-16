#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <fstream>
#include <algorithm>
#include "score.h"
#include "main.h"
#include "sevenseg.h"
using namespace std;

Score::Score(float x, float y) {
    this->x = x;
    this->y = y;
    this->Character[0] = SevenSeg(this->x, this->y);
    this->Character[1] = SevenSeg(this->x + 0.2, this->y);
    this->Character[2] = SevenSeg(this->x + 0.4, this->y);
    this->Character[3] = SevenSeg(this->x + 0.6, this->y);
    this->Character[4] = SevenSeg(this->x + 0.8, this->y);
    this->Character[5] = SevenSeg(this->x + 1.0, this->y);
    this->Character[6] = SevenSeg(this->x + 1.2, this->y);
    this->Character[7] = SevenSeg(this->x + 1.4, this->y);
    this->Character[8] = SevenSeg(this->x + 1.6, this->y);
    this->Character[9] = SevenSeg(this->x + 1.8, this->y);
    this->Character[10] = SevenSeg(this->x + 2.0, this->y);
}

void Score::draw(glm::mat4 VP, int score) {
    int dig;
    char c[6];
    for(int i=0; i<5; i++){
        dig = score%10;
        c[i] = dig + '0';
        score/=10;
    }
    this->Character[0].draw(VP, 's');
    this->Character[1].draw(VP, 'c'); 
    this->Character[2].draw(VP, 'o'); 
    this->Character[3].draw(VP, 'r'); 
    this->Character[4].draw(VP, 'e'); 
    this->Character[5].draw(VP, '-'); 
    this->Character[6].draw(VP, c[4]); 
    this->Character[7].draw(VP, c[3]); 
    this->Character[8].draw(VP, c[2]); 
    this->Character[9].draw(VP, c[1]); 
    this->Character[10].draw(VP, c[0]); 
}

void Score::tick() {
    for(int i=0; i < 11; i++)
        this->Character[i].tick();
}
