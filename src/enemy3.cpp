#include "enemy3.h"
#include "main.h"
#include <stdlib.h>
#include <stdio.h>

Enemy3::Enemy3(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = (rand() % 1800)/10.0;
    this->speed_x = 0.1f;
    this->speed_y = -0.016f;
    this->speed_rot = 3.0f;
    this->dir = -1;
    this->flag = 0;

    GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Enemy3::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we want to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Enemy3::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy3::move() {
    if(this->flag){
        this->rotation += this->speed_rot;
        this->position.x += (this->speed_x * this->dir);
        this->position.y += this->speed_y;
    }
}
