#include "piggy.h"
#include "main.h"

Piggy::Piggy(float y) {
    this->position = glm::vec3(300.0, y, 0);
    this->rotation = 0;
    speedx=-3;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[360*9];
    double angle;
    for(int i=0;i<360;i++){
        vertex_buffer_data[9*i]=0.0;
        vertex_buffer_data[9*i+1]=0.0;
        vertex_buffer_data[9*i+2]=0.0; 

        angle=i*2.0*PI/360.0;
        vertex_buffer_data[9*i+3]=30.0*cos(angle);
        vertex_buffer_data[9*i+4]=30.0*sin(angle);
        vertex_buffer_data[9*i+5]=0.0;
        // printf("%f %f\n", vertex_buffer_data[9*i+3], vertex_buffer_data[9*i+4]);

        angle=(i+1.0)*2.0*PI/360.0; 

        vertex_buffer_data[9*i+6]=30.0*cos(angle);
        vertex_buffer_data[9*i+7]=30.0*sin(angle);                
        vertex_buffer_data[9*i+8]=0.0;
    }
    this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, COLOR_PINK, GL_FILL);
}

void Piggy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Piggy::tick() {
    this->position.x +=speedx;
    this->position.y = 70.0+180.0*sin((this->position.x)/50.0);
}

