#include "main.h"

#ifndef EXTRALIVES_H
#define EXTRALIVES_H


class Extralives {
    public:
        Extralives() {}
        Extralives(float x, float y, color_t color);
        glm::vec3 position;
        float rotation;
        int taken;
        float speed;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        void move();

    private:
        VAO *object_left_top_semicircle;
        VAO *object_right_top_semicircle;
        VAO *object_triangles;
};

#endif // EXTRALIVES_H
