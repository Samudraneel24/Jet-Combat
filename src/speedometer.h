#include "main.h"
#include "sevenseg.h"
#include "semicircle2d.h"
#include "triangle.h"

#ifndef Speedometer_H
#define Speedometer_H

class Speedometer {
public:
    Speedometer() {}
    Speedometer(float x, float y);
    void draw(glm::mat4 VP);
    void tick(float speed);
    SevenSeg Character[5];
    Semicircle2d Out, In;
    Triangle T;
    float x, y;
private:
    VAO *object;
};

#endif // Speedometer_H
