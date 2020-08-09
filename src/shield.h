#include "main.h"

#ifndef SHIELD_H
#define SHIELD_H


class Shield {
    public:
        Shield() {}
        Shield(float x, float y, color_t color);
        glm::vec3 position;
        float rotation;
        int taken;
        float speed;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        void move();

    private:
        VAO *object_triangle1;
        VAO *object_triangle2;
        VAO *object_triangle3;
        VAO *object_quad;
};

#endif // SHIELD_H
