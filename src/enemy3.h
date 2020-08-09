#include "main.h"

#ifndef ENEMY3_H
#define ENEMY3_H


class Enemy3 {
    public:
        Enemy3() {}
        Enemy3(float x, float y, color_t color);
        glm::vec3 position;
        float rotation;
        float speed_x;
        float speed_y;
        float speed_rot;
        int dir;
        int flag;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        void move();

    private:
        VAO *object;
};

#endif // ENEMY3_H
