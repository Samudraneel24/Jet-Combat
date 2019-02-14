#include "main.h"
#include "sevenseg.h"

#ifndef SCORE_H
#define SCORE_H


class Score {
public:
    Score() {}
    Score(float x, float y);
    void draw(glm::mat4 VP, int score);
    void tick();
    SevenSeg Character[11];
    float x, y;
private:
    VAO *object;
};

#endif // SCORE_H
