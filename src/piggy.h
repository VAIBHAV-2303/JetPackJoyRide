#include "main.h"

#ifndef PIGGY_H
#define PIGGY_H


class Piggy {
public:
    Piggy() {}
    Piggy(float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    double speedx;
private:
    VAO *object;
    VAO *eyes;
    VAO *pupil;
    VAO *nose;
    VAO *nostrils;
};

#endif // PIGGY_H
