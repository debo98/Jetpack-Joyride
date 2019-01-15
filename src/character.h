#include "main.h"

#ifndef CHARACTER_H
#define CHARACTER_H


class Character {
    public:
        Character() {}
        Character(float x, float y, color_t color);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        void up();
        void down();
        void left(int magnetdir);
        void right(int magnetdir);
        double speed_x;
        double speed_y;
        double g;

    private:
        VAO *object_head;
        VAO *object_body;
};

#endif // CHARACTER_H
