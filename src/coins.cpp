#include "coins.h"
#include "main.h"
#include <stdio.h>

Coins::Coins(float x, float y, color_t color1, color_t color2, color_t color3) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->taken = 0;
    
    int n = 100;
    GLfloat vertex_buffer_data_coin[9*n];
    for(int i=0; i<9*n; i+=9){
        vertex_buffer_data_coin[i]   = (float)0.1*cos(((i/9))*2*3.14159265/n);
        vertex_buffer_data_coin[i+1] = (float)0.1*sin(((i/9))*2*3.14159265/n);
        vertex_buffer_data_coin[i+2] = 0.0f;
        vertex_buffer_data_coin[i+3] = (float)0.1*cos(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_coin[i+4] = (float)0.1*sin(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_coin[i+5] = 0.0f;
        vertex_buffer_data_coin[i+6] = 0.0f;
        vertex_buffer_data_coin[i+7] = 0.0f;
        vertex_buffer_data_coin[i+8] = 0.0f;
    }

    color_t color;
    int temp = rand() % 3;
    switch(temp % 3){
        case 0: color = color1; this->type = 0; break;
        case 1: color = color2; this->type = 1; break;
        case 2: color = color3; this->type = 2; break;
    }


    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_coin, color, GL_FILL);
}

void Coins::draw(glm::mat4 VP) {
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

void Coins::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
