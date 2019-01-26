#include "main.h"

#ifndef CHARACTER_H
#define CHARACTER_H


class Character {
    public:
        Character() {}
        Character(float x, float y, color_t color1, color_t color2, color_t color3, color_t color4);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP, int shield_on);
        void set_position(float x, float y);
        void up();
        void down();
        void left();
        void right();
        void magnet_pull();
        void update_score();
        double speed_x;
        double speed_y;
        double speed_due_to_magnet;
        double g;
        double a;
        int score;
        float distance_travelled;
        int ispoweredup;
        int lives;
        int coins_collected;
        int enemieskilled;
        int specialcoins_collected;

    private:
        VAO *object_head;
        VAO *object_body1;
        VAO *object_body2;
        VAO *object_leg1;
        VAO *object_leg2;
};

#endif // CHARACTER_H
