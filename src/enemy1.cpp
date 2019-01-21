#include "enemy1.h"
#include "main.h"
#include <stdlib.h>
#include <stdio.h>

Enemy1::Enemy1(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = (rand() % 1800)/10.0;
    
    int n = 100;
    GLfloat vertex_buffer_data_end1[9*n];
    for(int i=0; i<9*n; i+=9){
        vertex_buffer_data_end1[i]   = (float)0.1*cos(((i/9))*2*3.14159265/n);
        vertex_buffer_data_end1[i+1] = (float)0.1*sin(((i/9))*2*3.14159265/n);
        vertex_buffer_data_end1[i+2] = 0.0f;
        vertex_buffer_data_end1[i+3] = (float)0.1*cos(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_end1[i+4] = (float)0.1*sin(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_end1[i+5] = 0.0f;
        vertex_buffer_data_end1[i+6] = 0.0f;
        vertex_buffer_data_end1[i+7] = 0.0f;
        vertex_buffer_data_end1[i+8] = 0.0f;
    }

    GLfloat vertex_buffer_data_end2[9*n];
    for(int i=0; i<9*n; i+=9){
        vertex_buffer_data_end2[i]   = 1.0f + (float)0.1*cos(((i/9))*2*3.14159265/n);
        vertex_buffer_data_end2[i+1] = (float)0.1*sin(((i/9))*2*3.14159265/n);
        vertex_buffer_data_end2[i+2] = 0.0f;
        vertex_buffer_data_end2[i+3] = 1.0f + (float)0.1*cos(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_end2[i+4] = (float)0.1*sin(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_end2[i+5] = 0.0f;
        vertex_buffer_data_end2[i+6] = 1.0f;
        vertex_buffer_data_end2[i+7] = 0.0f;
        vertex_buffer_data_end2[i+8] = 0.0f;
    }

    GLfloat vertex_buffer_data_rod[] = {
        0.0f, 0.05f, 0.0f,
        0.0f, -0.05f, 0.0f,
        1.0f, 0.05f, 0.0f,
        1.0f, 0.05f, 0.0f,
        0.0f, -0.05f, 0.0f,
        1.0f, -0.05f, 0.0f,
    };

    this->object_end1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_end1, color, GL_FILL);
    this->object_end2 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_end2, color, GL_FILL);
    this->object_rod  = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_rod,  color, GL_FILL);
}

void Enemy1::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_end1);
    draw3DObject(this->object_end2);
    draw3DObject(this->object_rod);
}

void Enemy1::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
