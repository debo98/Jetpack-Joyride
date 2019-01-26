#include "main.h"

#ifndef SEMICIRCULARRING_H
#define SEMICIRCULARRING_H


class Semicircularring {
    public:
        Semicircularring() {}
        Semicircularring(float x, float y, color_t color);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);

    private:
        VAO *object;
};

#endif // SEMICIRCULARRING_H
