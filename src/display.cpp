#include "main.h"
#include "display.h"

Display::Display(float x, float y, color_t color) {

    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        10.0f,10.0f,0.0f, // triangle 1 : begin
        10.0f,0.0f, 0.0f,
        13.0f, 0.0f, 0.0f, // triangle 1 : end
        13.0f, 0.0f,0.0f, // triangle 2 : begin
        10.0f,10.0f,0.0f,
        13.0f, 10.0f,0.0f 
    };
    this->object[0] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);

    GLfloat vertex_buffer_data1[] = {
        10.0f,0.0f,0.0f, // triangle 1 : begin
        10.0f,-10.0f, 0.0f,
        13.0f, -10.0f, 0.0f, // triangle 1 : end
        13.0f, -10.0f,0.0f, // triangle 2 : begin
        10.0f,0.0f,0.0f,
        13.0f, 0.0f,0.0f         
    };
    this->object[1] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, color, GL_FILL);

    GLfloat vertex_buffer_data2[] = {
        0.0, -10.0, 0.0, 
        0.0, -7.0, 0.0,
        10.0, -10.0, 0.0,
        10.0, -10.0, 0.0,
        0.0, -7.0, 0.0,
        10.0, -7.0, 0.0
    };
    this->object[2] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, color, GL_FILL);

    GLfloat vertex_buffer_data3[] = {
        0.0f,0.0f,0.0f, // triangle 1 : begin
        0.0f,-10.0f, 0.0f,
        3.0f, -10.0f, 0.0f, // triangle 1 : end
        3.0f, -10.0f,0.0f, // triangle 2 : begin
        0.0f,0.0f,0.0f,
        3.0f, 0.0f,0.0f // triangle 2 : end
    };
    this->object[3] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, color, GL_FILL);

    GLfloat vertex_buffer_data4[] = {
        0.0f,10.0f,0.0f, // triangle 1 : begin
        0.0f,0.0f, 0.0f,
        3.0f, 0.0f, 0.0f, // triangle 1 : end
        3.0f, 0.0f,0.0f, // triangle 2 : begin
        0.0f,10.0f,0.0f,
        3.0f, 10.0f,0.0f // triangle 2 : end
    };
    this->object[4] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4, color, GL_FILL);

    GLfloat vertex_buffer_data5[] = {
        0.0, 10.0, 0.0, 
        0.0, 13.0, 0.0,
        10.0, 10.0, 0.0,
        10.0, 10.0, 0.0,
        0.0, 13.0, 0.0,
        10.0, 13.0, 0.0 // triangle 2 : end
    };
    this->object[5] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data5, color, GL_FILL);

    GLfloat vertex_buffer_data6[] = {
        0.0, 0.0, 0.0, 
        0.0, 3.0, 0.0,
        10.0, 0.0, 0.0,
        10.0, 0.0, 0.0,
        0.0, 3.0, 0.0,
        10.0, 3.0, 0.0 // triangle 2 : end
    };
    this->object[6] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data6, color, GL_FILL);
}

void Display::draw(glm::mat4 VP, float zoom, int num) {

	int numberMap[10][7]= {
        {1, 1, 1, 1, 1, 1, 0},
        {1, 1, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 0, 1, 1},
        {1, 1, 0, 0, 1, 0, 1},
        {0, 1, 1, 0, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1}
    };
   
    this->position.x/=zoom;
    this->position.y/=zoom;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<7;i++){
    	if(numberMap[num/100][i]==1){
    		draw3DObject(this->object[i]);
    	}
    }
    
    num%=100;
    this->position.x+=15;
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<7;i++){
    	if(numberMap[num/10][i]==1){
    		draw3DObject(this->object[i]);
    	}
    }
    
    num%=10;
    this->position.x+=15;
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<7;i++){
    	if(numberMap[num][i]==1){
    		draw3DObject(this->object[i]);
    	}
    }
    this->position.x-=30;
    this->position.x*=zoom;
    this->position.y*=zoom;
}
