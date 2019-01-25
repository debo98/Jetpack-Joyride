#include "enemy2.h"
#include "main.h"
#include <stdlib.h>
#include <stdio.h>

Enemy2::Enemy2(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.02;

    
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
        vertex_buffer_data_end2[i]   = 10.0f + (float)0.1*cos(((i/9))*2*3.14159265/n);
        vertex_buffer_data_end2[i+1] = (float)0.1*sin(((i/9))*2*3.14159265/n);
        vertex_buffer_data_end2[i+2] = 0.0f;
        vertex_buffer_data_end2[i+3] = 10.0f + (float)0.1*cos(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_end2[i+4] = (float)0.1*sin(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_end2[i+5] = 0.0f;
        vertex_buffer_data_end2[i+6] = 10.0f;
        vertex_buffer_data_end2[i+7] = 0.0f;
        vertex_buffer_data_end2[i+8] = 0.0f;
    }

    GLfloat vertex_buffer_data_end3[9*n];
    for(int i=0; i<9*n; i+=9){
        vertex_buffer_data_end3[i]   = (float)0.1*cos(((i/9))*2*3.14159265/n);
        vertex_buffer_data_end3[i+1] = 0.2f + (float)0.1*sin(((i/9))*2*3.14159265/n);
        vertex_buffer_data_end3[i+2] = 0.0f;
        vertex_buffer_data_end3[i+3] = (float)0.1*cos(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_end3[i+4] = 0.2f + (float)0.1*sin(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_end3[i+5] = 0.0f;
        vertex_buffer_data_end3[i+6] = 0.0f;
        vertex_buffer_data_end3[i+7] = 0.2f;
        vertex_buffer_data_end3[i+8] = 0.0f;
    }

    GLfloat vertex_buffer_data_end4[9*n];
    for(int i=0; i<9*n; i+=9){
        vertex_buffer_data_end4[i]   = 10.0f + (float)0.1*cos(((i/9))*2*3.14159265/n);
        vertex_buffer_data_end4[i+1] = 0.2f + (float)0.1*sin(((i/9))*2*3.14159265/n);
        vertex_buffer_data_end4[i+2] = 0.0f;
        vertex_buffer_data_end4[i+3] = 10.0f + (float)0.1*cos(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_end4[i+4] = 0.2f + (float)0.1*sin(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_end4[i+5] = 0.0f;
        vertex_buffer_data_end4[i+6] = 10.0f;
        vertex_buffer_data_end4[i+7] = 0.2f;
        vertex_buffer_data_end4[i+8] = 0.0f;
    }

    GLfloat vertex_buffer_data_beam[] = {
        0.0f, 0.25f, 0.0f,
        0.0f, -0.05f, 0.0f,
        10.0f, 0.25f, 0.0f,
        10.0f, 0.25f, 0.0f,
        0.0f, -0.05f, 0.0f,
        10.0f, -0.05f, 0.0f,
    };

    this->object_end1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_end1, color, GL_FILL);
    this->object_end2 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_end2, color, GL_FILL);
    this->object_end3 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_end3, color, GL_FILL);
    this->object_end4 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_end4, color, GL_FILL);
    this->object_beam  = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_beam,  color, GL_FILL);
}

void Enemy2::draw(glm::mat4 VP) {
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
    draw3DObject(this->object_end3);
    draw3DObject(this->object_end4);
    draw3DObject(this->object_beam);
}

void Enemy2::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy2::move() {
    if(this->position.y < -3.5 || this-> position.y > 3){
        this->speed *= -1;
    }
    this->position.y += this->speed;
}