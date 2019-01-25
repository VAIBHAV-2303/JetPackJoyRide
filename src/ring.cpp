#include "ring.h"
#include "main.h"
#include<math.h>

Ring::Ring(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    double angle;
    GLfloat vertex_buffer_data[360*9];
    for(int i=0;i<180;i++){
        angle=i*2.0*PI/360.0;
        vertex_buffer_data[18*i]=62.0*cos(angle);
        vertex_buffer_data[18*i+1]=62.0*sin(angle);
        vertex_buffer_data[18*i+2]=0.0; 

        vertex_buffer_data[18*i+3]=65.0*cos(angle);
        vertex_buffer_data[18*i+4]=65.0*sin(angle);
        vertex_buffer_data[18*i+5]=0.0;
        
        angle=(i+1.0)*2.0*PI/360.0;        
        vertex_buffer_data[18*i+6]=65.0*cos(angle);
        vertex_buffer_data[18*i+7]=65.0*sin(angle);
        vertex_buffer_data[18*i+8]=0.0; 
        

        angle=i*2.0*PI/360.0;
        vertex_buffer_data[18*i+9]=62.0*cos(angle);
        vertex_buffer_data[18*i+10]=62.0*sin(angle);
        vertex_buffer_data[18*i+11]=0.0; 

        angle=(i+1.0)*2.0*PI/360.0;        
        vertex_buffer_data[18*i+12]=65.0*cos(angle);
        vertex_buffer_data[18*i+13]=65.0*sin(angle);
        vertex_buffer_data[18*i+14]=0.0; 

        vertex_buffer_data[18*i+15]=62.0*cos(angle);
        vertex_buffer_data[18*i+16]=62.0*sin(angle);                
        vertex_buffer_data[18*i+17]=0.0;
    }
    this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, COLOR_GREY, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
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

void Ring::tick() {
    this->position.x-=2*Level;
}
