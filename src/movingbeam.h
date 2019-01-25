#include "main.h"

#ifndef MOVINGBEAM_H
#define MOVINGBEAM_H


class Movingbeam {
public:
    Movingbeam() {}
    Movingbeam(float x, float y);
    glm::vec3 position;
    int burning;
    float rotation;
    float dirn;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
};

#endif
