#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <fstream>
#include "sevenseg.h"
#include "main.h"
using namespace std;

SevenSeg::SevenSeg(float x, float y) {
    this->on = "1111111";
    this->x = this->orgx = x;
    this->y = this->orgy = y;
    this->R[0] = Rectangle2d(x, y, 0.15, 0.02, -90.0, COLOR_REALBLACK);
    this->R[1] = Rectangle2d(x, y - 0.15, 0.15, 0.02, -90.0, COLOR_REALBLACK);
    this->R[2] = Rectangle2d(x, y - 0.3, 0.15, 0.02, 0.0, COLOR_REALBLACK);
    this->R[3] = Rectangle2d(x + 0.15 - 0.02, y - 0.15, 0.15, 0.02, -90.0, COLOR_REALBLACK);
    this->R[4] = Rectangle2d(x + 0.15 - 0.02, y, 0.15, 0.02, -90.0, COLOR_REALBLACK);
    this->R[5] = Rectangle2d(x, y, 0.15, 0.02, 0.0, COLOR_REALBLACK);
    this->R[6] = Rectangle2d(x, y - 0.15, 0.15, 0.02, 0.0, COLOR_REALBLACK);
}

void SevenSeg::draw(glm::mat4 VP, char c) {
    this->c = c;
    if(c == '0' || c == 'o')
        this->on = "1111110";
    else if(c == '1')
        this->on = "0001100";
    else if(c == '2')
        this->on = "0110111";
    else if(c == '3')
        this->on = "0011111";
    else if(c == '4')
        this->on = "1001101";
    else if(c == '5' || c == 's')
        this->on = "1011011";
    else if(c == '6')
        this->on = "1111011";
    else if(c == '7')
        this->on = "0001110";
    else if(c == '8')
        this->on = "1111111";
    else if(c == '9')
        this->on = "1011111";
    else if(c == 'c')
        this->on = "1110010";
    else if(c == 'r')
        this->on = "1100010";
    else if(c == 'e')
        this->on = "1110011";
    else if(c == '-')
        this->on = "0000001";
    else if(c == 'l')
        this->on = "1110000";
    else if(c == 'v')
        this->on = "1111100";
    else if(c == 'a')
        this->on = "1101111";
    else if(c == 't')
        this->on = "1110001";
    else if(c == 'p')
        this->on = "1100111";
    else if(c == 'd')
        this->on = "0111101";
    for(int i=0; i<7; i++)
        if(this->on[i] == '1')
            this->R[i].draw(VP);
}

void SevenSeg::tick() {
    for(int i=0; i<7; i++)
        this->R[i].tick();
}
