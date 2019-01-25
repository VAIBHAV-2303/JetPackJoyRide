#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H


class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y);
    glm::vec3 position, bombPosition;
    int shot;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    double speed;
    double bombYspeed;
private:
    VAO *object;
    VAO *iceBomb1;
    VAO *iceBomb2;
};

#endif // DRAGON_H
