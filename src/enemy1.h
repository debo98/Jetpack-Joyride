#include "main.h"

#ifndef ENEMY1_H
#define ENEMY1_H


class Enemy1 {
    public:
        Enemy1() {}
        Enemy1(float x, float y, color_t color);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);

    private:
        VAO *object_end1;
        VAO *object_end2;
        VAO *object_rod;
};

#endif // ENEMY1_H
