#include "extralives.h"
#include "main.h"
#include <stdio.h>

Extralives::Extralives(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->taken = 0;
    this->speed = 0.1;
   

    int n = 100;
    GLfloat vertex_buffer_data_left_top_semicircle[9*n/2];
    for(int i=0; i<9*n/2; i+=9){
        vertex_buffer_data_left_top_semicircle[i]   = -0.1f + (float)0.1*cos(((i/9))*2*3.14159265/n);
        vertex_buffer_data_left_top_semicircle[i+1] = (float)0.1*sin(((i/9))*2*3.14159265/n);
        vertex_buffer_data_left_top_semicircle[i+2] = 0.0f;
        vertex_buffer_data_left_top_semicircle[i+3] = -0.1f + (float)0.1*cos(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_left_top_semicircle[i+4] = (float)0.1*sin(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_left_top_semicircle[i+5] = 0.0f;
        vertex_buffer_data_left_top_semicircle[i+6] = -0.1f;
        vertex_buffer_data_left_top_semicircle[i+7] = 0.0f;
        vertex_buffer_data_left_top_semicircle[i+8] = 0.0f;
    }

    GLfloat vertex_buffer_data_right_top_semicircle[9*n/2];
    for(int i=0; i<9*n/2; i+=9){
        vertex_buffer_data_right_top_semicircle[i]   = 0.1f + (float)0.1*cos(((i/9))*2*3.14159265/n);
        vertex_buffer_data_right_top_semicircle[i+1] = (float)0.1*sin(((i/9))*2*3.14159265/n);
        vertex_buffer_data_right_top_semicircle[i+2] = 0.0f;
        vertex_buffer_data_right_top_semicircle[i+3] = 0.1f + (float)0.1*cos(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_right_top_semicircle[i+4] = (float)0.1*sin(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_right_top_semicircle[i+5] = 0.0f;
        vertex_buffer_data_right_top_semicircle[i+6] = 0.1f;
        vertex_buffer_data_right_top_semicircle[i+7] = 0.0f;
        vertex_buffer_data_right_top_semicircle[i+8] = 0.0f;
    }

    GLfloat vertex_buffer_data_triangles[] = {
        0.0f, 0.0f, 0.0f,
        -0.2f, 0.0f, 0.0f,
        0.0f, -0.3f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.2f, 0.0f, 0.0f,
        0.0f, -0.3f, 0.0f,
    };

    this->object_left_top_semicircle = create3DObject(GL_TRIANGLES, n*3/2, vertex_buffer_data_left_top_semicircle, color, GL_FILL);
    this->object_right_top_semicircle = create3DObject(GL_TRIANGLES, n*3/2, vertex_buffer_data_right_top_semicircle, color, GL_FILL);
    this->object_triangles = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_triangles, color, GL_FILL);
}

void Extralives::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_left_top_semicircle);
    draw3DObject(this->object_right_top_semicircle);
    draw3DObject(this->object_triangles);
}

void Extralives::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Extralives::move() {
    if(this->position.y < -3.5 || this-> position.y > 3){
        this->speed *= -1;
    }
    this->position.y += this->speed;
}
