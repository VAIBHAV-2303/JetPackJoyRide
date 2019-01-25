#include "main.h"

#ifndef FIXEDBEAM_H
#define FIXEDBEAM_H


class Fixedbeam {
public:
    Fixedbeam() {}
    Fixedbeam(float x, float y, float angle);
    glm::vec3 position;
    int burning;
    float rotation;
    float angle;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
};

#endif // FIXEDBEAM_H
