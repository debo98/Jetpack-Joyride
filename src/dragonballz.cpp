#include "dragonballz.h"
#include "main.h"
#include <stdio.h>

Dragonballz::Dragonballz(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed_x = -0.01f;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    int n = 100;
    GLfloat vertex_buffer_data[9*n];
    for(int i=0; i<9*n; i+=9){
        vertex_buffer_data[i]   = (float)0.15*cos(((i/9))*2*3.14159265/n);
        vertex_buffer_data[i+1] = (float)0.15*sin(((i/9))*2*3.14159265/n);
        vertex_buffer_data[i+2] = 0.0f;
        vertex_buffer_data[i+3] = (float)0.15*cos(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data[i+4] = (float)0.15*sin(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data[i+5] = 0.0f;
        vertex_buffer_data[i+6] = 0.0f;
        vertex_buffer_data[i+7] = 0.0f;
        vertex_buffer_data[i+8] = 0.0f;
    }

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Dragonballz::draw(glm::mat4 VP) {
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

void Dragonballz::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dragonballz::move() {
    this->position.x += this->speed_x;
}
