#include "main.h"

#ifndef COINS_H
#define COINS_H


class Coins {
    public:
        Coins() {}
        Coins(float x, float y, color_t color1, color_t color2, color_t color3);
        glm::vec3 position;
        float rotation;
        int taken;
        int type;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);

    private:
        VAO *object;
};

#endif // COINS_H
