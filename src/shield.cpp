#include "shield.h"
#include "main.h"
#include <stdio.h>

Shield::Shield(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->taken = 0;
    this->speed = 0.1;
   

    GLfloat vertex_buffer_data_triangle1[] = {
        -0.1f, 0.325f, 0.0f,
        0.0f, 0.4f, 0.0f,
        0.1f, 0.325f, 0.0f,
    };

    GLfloat vertex_buffer_data_triangle2[] = {
        -0.2f, 0.3f, 0.0f,
        0.2f, 0.3f, 0.0f,
        0.0f, 0.35f, 0.0f,
    };

    GLfloat vertex_buffer_data_triangle3[] = {
        -0.1f, 0.1f, 0.0f,
        0.1f, 0.1f, 0.0f,
        0.0f, 0.0f, 0.0f,
    };

    GLfloat vertex_buffer_data_quad[] = {
        -0.2f, 0.3f, 0.0f,
        0.2f, 0.3f, 0.0f,
        -0.1f, 0.1f, 0.0f,
        -0.1f, 0.1f, 0.0f,
        0.2f, 0.3f, 0.0f,
        0.1f, 0.1f, 0.0f,
    };

    this->object_triangle1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_triangle1, color, GL_FILL);
    this->object_triangle2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_triangle2, color, GL_FILL);
    this->object_triangle3 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_triangle3, color, GL_FILL);
    this->object_quad = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_quad, color, GL_FILL);
}

void Shield::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_triangle1);
    draw3DObject(this->object_triangle2);
    draw3DObject(this->object_triangle3);
    draw3DObject(this->object_quad);
}

void Shield::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Shield::move() {
    if(this->position.y < -3.5 || this-> position.y > 3){
        this->speed *= -1;
    }
    this->position.y += this->speed;
}
