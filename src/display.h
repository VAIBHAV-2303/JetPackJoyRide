#include "main.h"

#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
public:
    Display() {}
    Display(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, float zoom, int num);
private:
    VAO *object[7];
};

#endif // Display_H
