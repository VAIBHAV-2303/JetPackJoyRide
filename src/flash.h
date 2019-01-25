#include "main.h"

#ifndef FLASH_H
#define FLASH_H


class Flash {
public:
    Flash() {}
    Flash(float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    double speedx;
private:
    VAO *object;
};

#endif // FLASH_H
