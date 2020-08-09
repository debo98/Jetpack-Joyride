#include "main.h"

#ifndef DRAGONBALLZ_H
#define DRAGONBALLZ_H


class Dragonballz {
    public:
        Dragonballz() {}
        Dragonballz(float x, float y, color_t color);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        void move();
        double speed_x;

    private:
        VAO *object;
};

#endif // DRAGONBALLZ_H
