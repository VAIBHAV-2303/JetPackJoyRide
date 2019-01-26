#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed=0;
    speedx=0;
    isSafeFor=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -10.0f,-10.0f,0.0f, // triangle 1 : begin
        -10.0f,10.0f, 0.0f,
        10.0f, -10.0f, 0.0f, // triangle 1 : end
        10.0f, -10.0f,0.0f, // triangle 2 : begin
        -10.0f,10.0f,0.0f,
        10.0f, 10.0f,0.0f, // triangle 2 : end
    };
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
    this->safeObject = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_GREEN, GL_FILL);
    double angle;
    for(int i=0;i<360;i++){
        this->counter_vertex_buffer_data[9*i]=0.0;
        this->counter_vertex_buffer_data[9*i+1]=23.0;
        this->counter_vertex_buffer_data[9*i+2]=0.0; 

        angle=i*2.0*PI/360.0;
        this->counter_vertex_buffer_data[9*i+3]=10.0*cos(angle);
        this->counter_vertex_buffer_data[9*i+4]=23.0+10.0*sin(angle);
        this->counter_vertex_buffer_data[9*i+5]=0.0;
        // printf("%f %f\n", vertex_buffer_data[9*i+3], vertex_buffer_data[9*i+4]);

        angle=(i+1.0)*2.0*PI/360.0; 

        this->counter_vertex_buffer_data[9*i+6]=10.0*cos(angle);
        this->counter_vertex_buffer_data[9*i+7]=23.0+10.0*sin(angle);                
        this->counter_vertex_buffer_data[9*i+8]=0.0;
    }
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(isSafeFor>0){
        draw3DObject(this->safeObject);
        this->counter = create3DObject(GL_TRIANGLES, (int)(isSafeFor*18.0/5.0), this->counter_vertex_buffer_data, COLOR_BLUE, GL_FILL);
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);    // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->counter);
    }
    else{
        draw3DObject(this->object);
    }
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->position.x +=speedx;
    this->position.x=std::max(-200.0f, this->position.x);
    this->position.x=std::min(290.0f, this->position.x);
    if(this->position.x==290.0){
        this->speedx=0;
    }
    this->position.y -= speed;
    this->position.y=std::min(290.0f, this->position.y);
    this->position.y=std::max(-140.0f, this->position.y);
    if(isSafeFor>0){
        isSafeFor--;
    }
}