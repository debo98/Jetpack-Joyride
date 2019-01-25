#include "character.h"
#include "main.h"
#include <stdio.h>

float camera_x;
float default_speed_x = 0.1, default_speed_y = 0.03;

Character::Character(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->score = 0;
    this->coins_collected = 0;
    this->specialcoins_collected = 0;
    this->lives = 3;
    g = 0.003;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data_body[] = {
        -0.2f, -0.8f, 0.0f,
        -0.2f, -0.2f, 0.0f,
        0.2f, -0.2f, 0.0f,
        -0.2f, -0.8f, 0.0f,
        0.2f, -0.8f, 0.0f,  
        0.2f, -0.2f, 0.0f,
    };

    int n = 100;
    GLfloat vertex_buffer_data_head[9*n];
    for(int i=0; i<9*n; i+=9){
        vertex_buffer_data_head[i]   = (float)0.2*cos(((i/9))*2*3.14159265/n);
        vertex_buffer_data_head[i+1] = (float)0.2*sin(((i/9))*2*3.14159265/n);
        vertex_buffer_data_head[i+2] = 0.0f;
        vertex_buffer_data_head[i+3] = (float)0.2*cos(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_head[i+4] = (float)0.2*sin(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_head[i+5] = 0.0f;
        vertex_buffer_data_head[i+6] = 0.0f;
        vertex_buffer_data_head[i+7] = 0.0f;
        vertex_buffer_data_head[i+8] = 0.0f;
    }

    this->object_body = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_body, color, GL_FILL);
    this->object_head = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_head, color, GL_FILL);
}

void Character::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_body);
    draw3DObject(this->object_head);
}

void Character::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Character::up() {
    if(this->position.y <= 3.3){
        speed_y = default_speed_y;
        this->position.y += speed_y;
        speed_y = 0;
    }
}

void Character::down() {
    if(this->position.y >= -3){
        speed_y += g;
        this->position.y -= speed_y;
    }
}

void Character::left(int magnetdir) {
    if(magnetdir == 0){
        if(this->position.x >= (camera_x - 3.7)){
            speed_x = default_speed_x;
            this->position.x -= speed_x;
            speed_x = 0;
        }
    }
}

void Character::right(int magnetdir) {
    if(magnetdir == 0){
        speed_x = default_speed_x;
        this->position.x += speed_x;
        // Change where the camera looks when character moves forward
        if(this->position.x >= camera_x)
            camera_x += speed_x; 
        speed_x = 0;
    }
}

void Character::update_score() {
    this->score = (10 * camera_x) + (5 * this->coins_collected) + (50 * this->specialcoins_collected);
}
