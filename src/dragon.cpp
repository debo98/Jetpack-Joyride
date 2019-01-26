#include "dragon.h"
#include "main.h"
#include <stdio.h>

Dragon::Dragon(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    int n = 100;
    GLfloat vertex_buffer_data_head[9*n];
    for(int i=0; i<9*n; i+=9){
        vertex_buffer_data_head[i]   = (float)0.5*cos(((i/9))*2*3.14159265/n);
        vertex_buffer_data_head[i+1] = (float)0.5*sin(((i/9))*2*3.14159265/n);
        vertex_buffer_data_head[i+2] = 0.0f;
        vertex_buffer_data_head[i+3] = (float)0.5*cos(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_head[i+4] = (float)0.5*sin(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_head[i+5] = 0.0f;
        vertex_buffer_data_head[i+6] = 0.0f;
        vertex_buffer_data_head[i+7] = 0.0f;
        vertex_buffer_data_head[i+8] = 0.0f;
    }
    
    GLfloat vertex_buffer_data_beak[] = {
        0.0f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        -1.25f, -0.3f, 0.0f,
    };

    GLfloat vertex_buffer_data_wing1[] = {
        0.6f, -0.5f, 0.0f,
        1.5f, -0.5f, 0.0f,
        1.60f, 0.5f, 0.0f,
    };

    GLfloat vertex_buffer_data_wing2[] = {
        1.25f, -0.5f, 0.0f,
        1.75f, -0.5f, 0.0f,
        1.85f, 0.5f, 0.0f,
    };

    GLfloat vertex_buffer_data_body[] = {
        0.0f, -0.5f, 0.0f,
        2.0f, -0.5f, 0.0f,
        0.0f, -1.5f, 0.0f,
        2.0f, -0.5f, 0.0f,
        0.0f, -1.5f, 0.0f,
        2.0f, -1.5f, 0.0f,
    };

    this->object_head = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_head, color, GL_FILL);
    this->object_beak = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_beak, color, GL_FILL);
    this->object_wing1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_wing1, color, GL_FILL);
    this->object_wing2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_wing2, color, GL_FILL);
    this->object_body = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_body, color, GL_FILL);
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
    draw3DObject(this->object_head);
    draw3DObject(this->object_beak);
    draw3DObject(this->object_wing1);
    draw3DObject(this->object_wing2);
    draw3DObject(this->object_body);
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
