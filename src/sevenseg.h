#include "main.h"
#include "rectangle2d.h"
#include <string>

using namespace std;

#ifndef SEVENSEG_H
#define SEVENSEG_H


class SevenSeg {
public:
    SevenSeg() {}
    SevenSeg(float x, float y);
    void draw(glm::mat4 VP, char c);
    void tick();
    Rectangle2d R[7];
    string on;
    float x, y, orgx, orgy;
    char c;
private:
    VAO *object;
};

#endif // SEVENSEG_H
