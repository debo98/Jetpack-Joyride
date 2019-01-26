#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H


class Dragon {
    public:
        Dragon() {}
        Dragon(float x, float y, color_t color);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);

    private:
        VAO *object_head;
        VAO *object_beak;
        VAO *object_wing1;
        VAO *object_wing2;
        VAO *object_body;
};

#endif // DRAGON_H
