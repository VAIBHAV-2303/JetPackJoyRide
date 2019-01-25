#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin {
public:
    Coin() {}
    Coin(float x, float y);
    glm::vec3 position;
    int taken;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
};

#endif // COIN_H
