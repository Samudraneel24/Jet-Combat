#include "main.h"
#include "sevenseg.h"
#include "rectangle2d.h"

#ifndef Fuelmeter_H
#define Fuelmeter_H


class Fuelmeter {
public:
    Fuelmeter() {}
    Fuelmeter(float x, float y);
    void draw(glm::mat4 VP);
    void tick(float fuel);
    SevenSeg Character[4];
    Rectangle2d Vert, Hor;
    float x, y;
private:
    VAO *object;
};

#endif // Fuelmeter_H
