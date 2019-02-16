#include "main.h"
#include "sevenseg.h"
#include "rectangle2d.h"

#ifndef Altitude_H
#define Altitude_H


class Altitude {
public:
    Altitude() {}
    Altitude(float x, float y);
    void draw(glm::mat4 VP);
    void tick(float altitude);
    SevenSeg Character[3];
    Rectangle2d Vert, Hor;
    float x, y;
private:
    VAO *object;
};

#endif // Altitude_H
