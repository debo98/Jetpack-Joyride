#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    float x;
    float y;
    float width;
    float height;
};

bool detect_collision(bounding_box_t a, bounding_box_t b, float theta);
bool opposite_sides(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

extern float screen_zoom, screen_center_x, screen_center_y;
extern float camera_x;
extern float default_speed_x, default_speed_y;
void reset_screen();

void generate_coins();
void generate_enemy1(); 
void generate_enemy2();
void generate_enemy3();
void generate_specialcoins();
void generate_extralives();
void generate_shields();
void generate_semicircularring();

void make_enemy3_move();
void make_magnet_move();
void make_dragon_move();
void dragon_spits_ice();
void move_on_ring();

void detect_collision_with_coins();
void detect_collision_with_enemy1();
void detect_collision_with_enemy2();
void detect_collision_with_enemy3();
void detect_collision_with_semicircularring();
void detect_collision_with_dragonballz();
void detect_collision_with_specialcoins();
void detect_collision_with_extralives();
void detect_collision_with_shields();
void detect_collision_of_balloon_with_enemy1();
void detect_collision_of_balloon_with_enemy2();

void lose_life();
void game_over();

// ---- Colors ----
extern const color_t COLOR_FULLRED;
extern const color_t COLOR_RED;
extern const color_t COLOR_HEARTRED;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_ICEBLUE;
extern const color_t COLOR_BLUE;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_YELLOW;
extern const color_t COLOR_ORANGE;
extern const color_t COLOR_DARKORANGE;
extern const color_t COLOR_GOLD;
extern const color_t COLOR_SKIN;
extern const color_t COLOR_JEANS;
extern const color_t COLOR_BACKGROUND;

#endif
