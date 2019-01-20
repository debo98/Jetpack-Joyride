#include "main.h"

#ifndef BG_H
#define BG_H


class Bg {
    public:
        Bg() {}
        Bg(float x, float y, color_t color);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);

    private:
        VAO *object;
};

#endif // BG_H
