#include "main.h"

#ifndef SPECIALCOINS_H
#define SPECIALCOINS_H


class Specialcoins {
    public:
        Specialcoins() {}
        Specialcoins(float x, float y, color_t color);
        glm::vec3 position;
        float rotation;
        int taken;
        float speed;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        void move();

    private:
        VAO *object;
};

#endif // SPECIALCOINS_H
