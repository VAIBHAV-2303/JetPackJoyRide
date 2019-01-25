#include "dragon.h"
#include "main.h"

Dragon::Dragon(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed=2;
    shot=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -10.0, 30.0, 0.0,
        10.0, 20.0 ,0.0,
        10.0, 40.0, 0.0,

        9.339746, 34.000000, 0.0,
        21.660254, 18.660254, 0.0,
        31.660255, 32.660254, 0.0,

        24.718346, 23.933030, 0.0,
        23.454830, 2.620901, 0.0,
        40.962780, 7.312977, 0.0,

        29.434486, 1.222580, 0.0,
		17.998295, -18.510647, 0.0,
		35.817402, -22.667053, 0.0
	};
    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_WATER, GL_FILL);

    static const GLfloat iceBomb1_vertex_buffer_data[]= {
        -10.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 20.0, 0.0,

        -3.090170, -9.510566, 0.0,
        0.000000, 0.000000, 0.0,
        -19.021132, 6.180339, 0.0,

        8.089685, -5.877516, 0.0,
        0.000000, 0.000000, 0.0,
        -11.755032, -16.179371, 0.0,

        8.079559, 5.870607, 0.0,
        0.000000, 0.000000, 0.0,
        11.746090, -16.176474, 0.0,

        -3.088935, 9.488955, 0.0,
        0.000000, 0.000000, 0.0,
        19.006443, 6.168599, 0.0

    };
    this->iceBomb1 = create3DObject(GL_TRIANGLES, 5*3, iceBomb1_vertex_buffer_data, COLOR_WATER, GL_FILL);    

    static const GLfloat iceBomb2_vertex_buffer_data[]= {
        10.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 20.0, 0.0,

      	3.090170, 9.510566, 0.0,
		0.000000, 0.000000, 0.0,
		-19.021132, 6.180339, 0.0,

		-8.089685, 5.877516, 0.0,
		0.000000, 0.000000, 0.0,
		-11.755032, -16.179371, 0.0,

		-8.079559, -5.870607, 0.0,
		0.000000, 0.000000, 0.0,
		11.747635, -16.171719, 0.0,

		3.088935, -9.488955, 0.0,
		0.000000, 0.000000, 0.0,
		19.006443, 6.168599, 0.0
    };	
    this->iceBomb2 = create3DObject(GL_TRIANGLES, 5*3, iceBomb2_vertex_buffer_data, COLOR_BACKGROUND, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

    if(this->shot==1){
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->bombPosition);    // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
        // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
        // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->iceBomb1);        
        draw3DObject(this->iceBomb2);
    }
}

void Dragon::tick() {
    this->position.y -= speed;
    if(this->position.y>=270.0f){
        this->speed=-1.0*speed;
    }
    if(this->position.y<=-120.0f){
        this->speed=-1.0*speed;
    }

    if(this->shot==0){
        this->shot=1;
        this->bombPosition.x = this->position.x;
        this->bombPosition.y = this->position.y;
        this->bombYspeed=3;
    }
    else{
        this->bombPosition.x-=5;
        if(this->bombPosition.x<-400.0){
            this->shot=0;
        }
        this->bombPosition.y+=bombYspeed;
        if(this->bombPosition.y<=-140.0){
        	this->shot=0;
        }
        this->bombYspeed-=(3/20.0);
    }
}