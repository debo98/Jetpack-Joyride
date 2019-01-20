#include "main.h"

#ifndef COINS_H
#define COINS_H


class Coins {
    public:
        Coins() {}
        Coins(float x, float y, color_t color);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);

    private:
        VAO *object_head;
        VAO *object_body;
};

#endif // COINS_H
