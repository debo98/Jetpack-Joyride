#include "main.h"

#ifndef ENEMY2_H
#define ENEMY2_H


class Enemy2 {
    public:
        Enemy2() {}
        Enemy2(float x, float y, color_t color);
        glm::vec3 position;
        float rotation;
        float speed;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        void move();

    private:
        VAO *object_end1;
        VAO *object_end2;
        VAO *object_end3;
        VAO *object_end4;
        VAO *object_beam;
};

#endif // ENEMY2_H
