#include "main.h"

#ifndef WATERBALLOON_H
#define WATERBALLOON_H


class Waterballoon {
    public:
        Waterballoon() {}
        Waterballoon(float x, float y, color_t color);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        void move();
        double speed_x;
        double speed_y;
        double g;

    private:
        VAO *object;
};

#endif // WATERBALLOON_H
