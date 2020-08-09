#include "main.h"

#ifndef PROPULSION_H
#define PROPULSION_H


class Propulsion {
    public:
        Propulsion() {}
        Propulsion(float x, float y, color_t color);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);

    private:
        VAO *object_triangle1;
        VAO *object_triangle2;
        VAO *object_triangle3;
};

#endif // PROPULSION_H
