#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
	Boomerang(){}
    Boomerang(float x);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BOOMERANG_H
