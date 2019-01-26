#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
    public:
        Magnet() {}
        Magnet(float x, float y, color_t color1, color_t color2);
        glm::vec3 position;
        float rotation;
        int is_active;
        float start;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        void appear();

    private:
        VAO *object_left;
        VAO *object_top;
        VAO *object_bottom;
};

#endif // MAGNET_H
