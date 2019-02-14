#include "main.h"
#include "sevenseg.h"

#ifndef Altitude_H
#define Altitude_H


class Altitude {
public:
    Altitude() {}
    Altitude(float x, float y);
    void draw(glm::mat4 VP, int Altitude);
    void tick();
    SevenSeg Character[9];
    float x, y;
private:
    VAO *object;
};

#endif // Altitude_H
