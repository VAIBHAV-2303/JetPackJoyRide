#include "fixedbeam.h"
#include "main.h"

Fixedbeam::Fixedbeam(float x, float y, float angle) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = angle;
    this->angle = angle;
    this->burning=1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    const GLfloat vertex_buffer_data[] = {
        -60.0,0.0,0.0,
        -60.0,5.0, 0.0,
        60.0, 0.0,0.0, 
         60.0, 0.0,0.0, 
        -60.0,5.0, 0.0,
        60.0, 5.0,0.0,
    
        // Square 1
        -60.0+10.0, 10.0, 0.0,
        -60.0+10.0, -10.0, 0.0,
        -60.0-10.0, -10.0, 0.0,
        -60.0-10.0, -10.0, 0.0,
        -60.0+10.0, 10.0, 0.0,
        -60.0-10.0, 10.0, 0.0,

        // Square 2
        60.0+10.0, 10.0, 0.0,
        60.0+10.0, -10.0, 0.0,
        60.0-10.0, -10.0, 0.0,
        60.0-10.0, -10.0, 0.0,
        60.0+10.0, 10.0, 0.0,
        60.0-10.0, 10.0, 0.0,
    };
    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, COLOR_FLAME, GL_FILL);
}

void Fixedbeam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Fixedbeam::tick() {
    this->position.x-=2*Level;
}