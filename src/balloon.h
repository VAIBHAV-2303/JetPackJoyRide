#include "main.h"

#ifndef BALLOON_H
#define BALLOON_H


class Balloon {
public:
    Balloon() {}
    Balloon(float x, float y);
    glm::vec3 position;
    float rotation;
    int burst;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double speedx;
private:
    VAO *object;
};

#endif // BALLOON_H
