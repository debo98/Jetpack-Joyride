#include "character.h"
#include "main.h"
#include <stdio.h>

float camera_x;
float default_speed_x = 0.1, default_speed_y = 0.03;

Character::Character(float x, float y, color_t color1, color_t color2, color_t color3, color_t color4) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed_x = 0.1;
    this->speed_due_to_magnet = 0;
    this->score = 0;
    this->distance_travelled = 0;
    this->yellow_coins_collected = 0;
    this->black_coins_collected = 0;
    this->green_coins_collected = 0;
    this->specialcoins_collected = 0;
    this->ispoweredup = 0;
    this->lives = 3;
    this->enemieskilled = 0;
    this->on_ring = 0;
    this->a = 0;
    g = 0.003;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data_body[] = {
        -0.2f, -0.5f, 0.0f,
        -0.2f, -0.2f, 0.0f,
        0.2f, -0.2f, 0.0f,
        -0.2f, -0.5f, 0.0f,
        0.2f, -0.5f, 0.0f,  
        0.2f, -0.2f, 0.0f,
    };

    GLfloat vertex_buffer_data_leg1[] = {
        -0.2f, -0.5f, 0.0f,
        -0.2f, -0.8f, 0.0f,
        -0.02f, -0.5f, 0.0f,
        -0.2f, -0.8f, 0.0f,
        -0.02f, -0.5f, 0.0f, 
        -0.02f, -0.8f, 0.0f,
    };

    GLfloat vertex_buffer_data_leg2[] = {
        0.2f, -0.5f, 0.0f,
        0.2f, -0.8f, 0.0f,
        0.02f, -0.5f, 0.0f,
        0.2f, -0.8f, 0.0f,
        0.02f, -0.5f, 0.0f, 
        0.02f, -0.8f, 0.0f,
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

    this->object_body1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_body, color1, GL_FILL);
    this->object_body2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_body, color2, GL_FILL);
    this->object_head = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_head, color3, GL_FILL);
    this->object_leg1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_leg1, color4, GL_FILL);
    this->object_leg2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_leg2, color4, GL_FILL);
}

void Character::draw(glm::mat4 VP, int shield_on) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object_head);
    draw3DObject(this->object_leg1);
    draw3DObject(this->object_leg2);
    if(shield_on){
        draw3DObject(this->object_body2);
    }
    else{
        draw3DObject(this->object_body1);
    }
}

void Character::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Character::up() {
    if(!this->on_ring && this->position.y <= 3.3){
        speed_y = default_speed_y;
        this->position.y += speed_y;
        speed_y = 0;
    }
}

void Character::down() {
    if(!this->on_ring && this->position.y >= -3){
        speed_y += g;
        this->position.y -= speed_y;
    }
}

void Character::left() {
    if(!this->on_ring && this->position.x >= (camera_x - 3.7)){
        this->position.x -= this->speed_x;
    }
}

void Character::right() {
    this->position.x += this->speed_x;
    // Change where the camera looks when character moves forward
    if(this->position.x >= camera_x){
        camera_x += this->speed_x; 
        this->distance_travelled += this->speed_x;
    }
}

void Character::magnet_pull(){
    if(this->a != 0){
        this->speed_due_to_magnet += a;
    }
    else{
        this->speed_due_to_magnet = 0;
    }
    if(this->position.x >= camera_x - 3.7){
        this->position -= this->speed_due_to_magnet;
    }
}

void Character::update_score() {
    this->score = (10 * this->distance_travelled) + (1 * this->yellow_coins_collected) + (2 * this->black_coins_collected) + (5 * this->green_coins_collected) + (10 * this->enemieskilled) + (50 * this->specialcoins_collected);
}
