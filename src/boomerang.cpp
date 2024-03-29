#include "boomerang.h"
#include "main.h"

Boomerang::Boomerang(float x) {
    this->position = glm::vec3(x, 290.0, 0);
    this->rotation = 0;
    this->speed=-3;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -30.0f,0.0f,0.0f, // triangle 1 : begin
        -10.0f,0.0f, 0.0f,
        10.0f, 14.0f, 0.0f, // triangle 1 : end
        -30.0f, 0.0f,0.0f, // triangle 2 : begin
        -10.0f,0.0f,0.0f,
        10.0f, -14.0f,0.0f // triangle 2 : end
    };
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_CREAM, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
void Boomerang::tick() {
    this->rotation+=15;
    this->position.y+=speed;
    this->position.x=((this->position.y-100.0)*(this->position.y-100.0)/70.0)-200.0;
}

