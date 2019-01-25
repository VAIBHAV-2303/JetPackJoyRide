#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double speedx;
    int isSafeFor;
    GLfloat counter_vertex_buffer_data[360*9];
private:
    VAO *object;
    VAO *safeObject;
    VAO *counter;
};

#endif // BALL_H
