#include "main.h"

#ifndef DIAMOND_H
#define DIAMOND_H


class Diamond {
public:
    Diamond() {}
    Diamond(float x, float y);
    glm::vec3 position;
    int taken;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
};

#endif // DIAMOND_H
