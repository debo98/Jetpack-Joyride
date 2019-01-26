#include "magnet.h"
#include "main.h"
#include <stdio.h>

Magnet::Magnet(float x, float y, color_t color1, color_t color2) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->is_active = 0;

    GLfloat vertex_buffer_data_left[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 1.8f, 0.0f,
        0.2f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.8f, 0.0f,
        0.2f, 1.8f, 0.0f,
    };

    GLfloat vertex_buffer_data_top[] = {
        0.2f, 0.0f, 0.0f,
        0.2f, 0.45f, 0.0f,
        0.4f, 0.45f, 0.0f,
        0.2f, 0.0f, 0.0f,
        0.4f, 0.0f, 0.0f,
        0.4f, 0.45f, 0.0f,
    };

    GLfloat vertex_buffer_data_bottom[] = {
        0.2f, 1.35f, 0.0f,
        0.2f, 1.8f, 0.0f,
        0.4f, 1.8f, 0.0f,
        0.2f, 1.35f, 0.0f,
        0.4f, 1.35f, 0.0f,
        0.4f, 1.8f, 0.0f,
    };

    this->object_left = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_left, color1, GL_FILL);
    this->object_top = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_top, color2, GL_FILL);
    this->object_bottom = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_bottom, color2, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_left);
    draw3DObject(this->object_top);
    draw3DObject(this->object_bottom);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::appear(){
    this->is_active = 1;
    this->position.x = camera_x - 3.8f;
}

