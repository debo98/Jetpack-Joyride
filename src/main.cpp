#include "main.h"
#include "timer.h"
#include "character.h"
#include "coins.h"
#include "bg.h"
#include "enemy1.h"
#include "enemy2.h"
#include "enemy3.h"
#include "specialcoins.h"
#include "extralives.h"
#include "shield.h"
#include "propulsion.h"
#include "dragon.h"
#include "dragonballz.h"
#include "waterballoon.h"
#include "magnet.h"
#include "semicircularring.h"
#include <stdio.h>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Character character;
Propulsion propulsion;
Bg bg_floor, bg_roof;
Dragon dragon;
Dragonballz dragonballz;
Waterballoon waterballoon;
Magnet magnet;
#define number_of_coins 300
#define length_of_game 1000
Coins coins[number_of_coins];
#define number_of_enemy1 100
Enemy1 enemy1[number_of_enemy1];
#define number_of_enemy2 20
Enemy2 enemy2[number_of_enemy2];
#define number_of_enemy3 6
Enemy3 enemy3[number_of_enemy3];
#define number_of_specialcoins 4
Specialcoins specialcoins[number_of_specialcoins];
#define number_of_extralives 4
Extralives extralives[number_of_extralives];
#define number_of_shields 4
Shield shield[number_of_shields];
#define number_of_semicircularring 40
Semicircularring semicircularring[number_of_semicircularring];

bounding_box_t box_character, box_object, box_object2;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

int powerdown_at;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye (camera_x, 0, 1);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (camera_x, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    character.draw(VP, character.ispoweredup);
    propulsion.draw(VP);
    bg_floor.draw(VP);
    bg_roof.draw(VP);
    if(dragon.visible){
        dragon.draw(VP);
    }
    dragonballz.draw(VP);
    if(magnet.is_active){
        magnet.draw(VP);  
    }
    waterballoon.draw(VP);
    for (int i = 0; i < number_of_coins; i++) {
        if(!coins[i].taken){
            coins[i].draw(VP); 
        }
    }
    for (int i = 0; i < number_of_enemy1; i++) {
        enemy1[i].draw(VP);
    }
    for (int i = 0; i < number_of_enemy2; i++) {
        enemy2[i].draw(VP);
    }
    for (int i = 0; i < number_of_enemy3; i++) {
        enemy3[i].draw(VP);
    }
    for (int i = 0; i < number_of_specialcoins; i++) {
        specialcoins[i].draw(VP);
    }
    for (int i = 0; i < number_of_extralives; i++) {
        extralives[i].draw(VP);
    }
    for (int i = 0; i < number_of_shields; i++) {
        shield[i].draw(VP);
    }
    for (int i = 0; i < number_of_semicircularring; i++) {
        semicircularring[i].draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    glfwSetScrollCallback(window, scroll_callback);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int shoot = glfwGetKey(window, GLFW_KEY_UP);
    if (left)
        character.left();
    if (right)
        character.right();
    if (up){
        character.up();
        propulsion.position.x = character.position.x;
        propulsion.position.y = character.position.y - 0.8f;
    }
    else{
        character.down();
        propulsion.position.x = -500.0f;
        propulsion.position.y = -500.0f;
    }
    if(shoot && (waterballoon.position.x <= -400.0f)){
        waterballoon.position.x = character.position.x + 0.3f;
        waterballoon.position.y = character.position.y - 0.35f;
    }
    reset_screen();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // Generate Barry Steakfries
    character = Character(-3.0f, -3.0f, COLOR_RED, COLOR_FULLRED, COLOR_SKIN, COLOR_JEANS);
    propulsion = Propulsion(-500.0f, -500.0f, COLOR_GOLD);
    bg_floor = Bg(0.0f, 0.0f, COLOR_GREEN);
    bg_roof = Bg(0.0f, 13.6f, COLOR_GREEN);
    dragon = Dragon((rand()%(1000))/10.0 + 500, 0.0f, COLOR_BLACK);
    dragon.start = dragon.position.x;
    dragonballz = Dragonballz(-500.0f, 0.0f, COLOR_ICEBLUE);
    waterballoon = Waterballoon(-500.0f, 0.0f, COLOR_BLUE);
    magnet = Magnet((rand()%(1000))/10.0 + 400, (rand()%55)/10.0 - 3.5, COLOR_BLUE, COLOR_FULLRED);
    magnet.start = magnet.position.x;
    
    generate_coins();
    generate_enemy1();
    generate_enemy2();
    generate_enemy3();
    generate_specialcoins();
    generate_extralives();
    generate_shields();
    generate_semicircularring();
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    /* Game Loop */
    while (!glfwWindowShouldClose(window)) {
    
        // Process timers
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_input(window);
            
            // Changing background as the character moves forward
            glm::vec3 eye (camera_x, 0, 1);
            glm::vec3 target (camera_x, 0, 0);

            for (int i = 0; i < number_of_enemy2; i++) {
                enemy2[i].move();
            }
            for (int i = 0; i < number_of_enemy3; i++) {
                enemy3[i].move();
            }
            for (int i = 0; i < number_of_specialcoins; i++) {
                specialcoins[i].move();
            }
            for (int i = 0; i < number_of_extralives; i++) {
                extralives[i].move();
            }
            for (int i = 0; i < number_of_shields; i++) {
                shield[i].move();
            }

            make_magnet_move();
            make_enemy3_move();
            make_dragon_move();
            dragonballz.move();
            waterballoon.move();
            character.magnet_pull();
            if(character.on_ring){
                move_on_ring();
            }

            box_character.x = character.position.x - 0.2f;
            box_character.y = character.position.y - 0.8f;
            box_character.width = 0.4f;
            box_character.height = 1.0f;
            character.update_score();
            if(character.position.x >= powerdown_at){
                character.ispoweredup = 0;
            }

            detect_collision_with_coins();
            detect_collision_with_enemy1();
            detect_collision_with_enemy2();
            detect_collision_with_enemy3();
            detect_collision_with_specialcoins();
            detect_collision_with_extralives();
            detect_collision_with_shields();
            detect_collision_with_semicircularring();
            detect_collision_with_dragonballz();
            detect_collision_of_balloon_with_enemy1();
            detect_collision_of_balloon_with_enemy2();

            printf("Lives left : %d\n", character.lives);
            printf("Game Score : %d\n", character.score);
            printf("Level : %d\n", (1 + ((int)camera_x)/100));

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool opposite_sides(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    float temp1, temp2, temp3, temp4;
    temp1 = (y2-y1)*(x3-x2) - (x2-x1)*(y3-y2);
    if(temp1 > 0)
        temp1 = 1;
    else if(temp1 < 0)
        temp1 = -1;
    temp2 = (y2-y1)*(x4-x2) - (x2-x1)*(y4-y2);
    if(temp2 > 0)
        temp2 = 1;
    else if(temp2 < 0)
        temp2 = -1;
    temp3 = (y4-y3)*(x1-x4) - (x4-x3)*(y1-y4);
    if(temp3 > 0)
        temp3 = 1;
    else if(temp3 < 0)
        temp3 = -1;
    temp4 = (y4-y3)*(x2-x4) - (x4-x3)*(y2-y4);
    if(temp4 > 0)
        temp4 = 1;
    else if(temp4 < 0)
        temp4 = -1;
    return temp1!=temp2 && temp3!=temp4;
}

// a is character, b is object, theta is the rotation angle of object
bool detect_collision(bounding_box_t a, bounding_box_t b, float theta) {
    return  opposite_sides(a.x, a.y, a.x+a.width, a.y, b.x, b.y, b.x+b.width*cos(theta), b.y+b.width*sin(theta)) ||
            opposite_sides(a.x, a.y, a.x+a.width, a.y, b.x-b.height*sin(theta), b.y+b.height*cos(theta), b.x-b.height*sin(theta)+b.width*cos(theta), b.y+b.height*cos(theta)+b.width*sin(theta)) ||
            opposite_sides(a.x, a.y+a.height, a.x+a.width, a.y+a.height, b.x, b.y, b.x+b.width*cos(theta), b.y+b.width*sin(theta)) ||
            opposite_sides(a.x, a.y+a.height, a.x+a.width, a.y+a.height, b.x-b.height*sin(theta), b.y+b.height*cos(theta), b.x-b.height*sin(theta)+b.width*cos(theta), b.y+b.height*cos(theta)+b.width*sin(theta)) ||
            opposite_sides(a.x, a.y, a.x, a.y+a.height, b.x, b.y, b.x+b.width*cos(theta), b.y+b.width*sin(theta)) ||
            opposite_sides(a.x, a.y, a.x, a.y+a.height, b.x-b.height*sin(theta), b.y+b.height*cos(theta), b.x-b.height*sin(theta)+b.width*cos(theta), b.y+b.height*cos(theta)+b.width*sin(theta)) ||
            opposite_sides(a.x, a.y, a.x+a.width, a.y+a.height, b.x, b.y, b.x+b.width*cos(theta), b.y+b.width*sin(theta)) ||
            opposite_sides(a.x, a.y, a.x+a.width, a.y+a.height, b.x-b.height*sin(theta), b.y+b.height*cos(theta), b.x-b.height*sin(theta)+b.width*cos(theta), b.y+b.height*cos(theta)+b.width*sin(theta));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}


/* Initialising objects in game */
// Level 1
void generate_coins() {
    for (int i = 0; i < number_of_coins; i++) {
        coins[i] = Coins ((rand()%(10*length_of_game))/10.0 + 4, (rand()%60)/10.0 - 3, COLOR_YELLOW, COLOR_BLACK, COLOR_GREEN);
    }
}

// Level 2
void generate_enemy1() {
    for (int i = 0; i < number_of_enemy1; i++) {
        enemy1[i] = Enemy1 ((rand()%(10*length_of_game - 100))/10.0 + 100, (rand()%60)/10.0 - 3.5, COLOR_ORANGE);
    }
}

// Level 3
void generate_enemy2() {
    for (int i = 0; i < number_of_enemy2; i++) {
        enemy2[i] = Enemy2 ((rand()%(10*length_of_game - 200))/10.0 + 200, (rand()%65)/10.0 - 3.5, COLOR_DARKORANGE);
    }
}

// Level 4
void generate_enemy3() {
    for (int i = 0; i < number_of_enemy3; i++) {
        enemy3[i] = Enemy3 ((rand()%(10*length_of_game - 300))/10.0 + 300, (rand()%10)/10.0 + 2.0, COLOR_DARKORANGE);
    }
}

void generate_specialcoins() {
    for (int i = 0; i < number_of_specialcoins; i++) {
        specialcoins[i] = Specialcoins ((rand()%(10*length_of_game - 150))/10.0 + 150, (rand()%60)/10.0 - 3, COLOR_YELLOW);
    }
}

void generate_extralives() {
    for (int i = 0; i < number_of_extralives; i++) {
        extralives[i] = Extralives ((rand()%(10*length_of_game - 150))/10.0 + 150, (rand()%60)/10.0 - 3, COLOR_HEARTRED);
    }
}

void generate_shields() {
    for (int i = 0; i < number_of_shields; i++) {
        shield[i] = Shield ((rand()%(10*length_of_game - 150))/10.0 + 150, (rand()%60)/10.0 - 3, COLOR_GREEN);
    }
}

void generate_semicircularring() {
    for (int i = 0; i < number_of_semicircularring; i++) {
        semicircularring[i] = Semicircularring ((rand()%(10*length_of_game - 150))/10.0 + 150, (rand()%60)/10.0 - 3, COLOR_BLACK);
    }
}

// The boomerang comes
void make_enemy3_move() {
    for (int i = 0; i < number_of_enemy3; i++) {
        if(!enemy3[i].flag && enemy3[i].position.x - character.position.x <= 7.5){
            enemy3[i].flag = 1;
        }
        if(enemy3[i].flag && enemy3[i].position.y <= 0){
            enemy3[i].dir = 1;
        }
        if(enemy3[i].position.y <= -3){
            enemy3[i].position.x = -500.0f;
            enemy3[i].position.y = -500.0f;
        }
    }
}

// The Magnet appears
void make_magnet_move() {
    if(camera_x >= magnet.position.x && magnet.position.x - magnet.start <= 20.0){
        if((character.position.y <= magnet.position.y + 2.5) && (character.position.y >= magnet.position.y + 0.5)){
            character.a = 0.0003;
        }
        else{
            character.a = 0;
        }
        magnet.appear();
    }
    if(magnet.position.x - magnet.start >= 20.0){
        character.a = 0;
        magnet.is_active = 0;
        magnet.start += ((rand()%1000)/10.0 + 100.0);
        magnet.position.x = magnet.start;
        magnet.position.y = (rand()%65)/10.0 - 3.5;
    }
}

// The Dragon appears
void make_dragon_move() {
    if(camera_x + 3.0f >= dragon.position.x && dragon.position.x - dragon.start <= 20.0){
        dragon.appear(character.position.y);
        if(dragon.fire[(int)(dragon.position.x-dragon.start)]){
            dragon.fire[(int)(dragon.position.x-dragon.start)] = 0;
            dragon_spits_ice();
        }
    }
    if(dragon.position.x - dragon.start >= 20.0){
        dragon.visible = 0;
        dragon.start += ((rand()%1000)/10.0 + 100.0);
        dragon.position.x = dragon.start;
        for(int i=0; i<20; i++){
            dragon.fire[i] = 1;
        }
    }
}

// Generate ice ball
void dragon_spits_ice() {
    dragonballz.position.x = dragon.position.x - 1.4f;
    dragonballz.position.y = dragon.position.y - 0.45f;
}

/* Collisions */
// Collecting coins
void detect_collision_with_coins() {
    for (int i = 0; i < number_of_coins; i++) {
        box_object.x = coins[i].position.x - 0.1f;
        box_object.y = coins[i].position.y - 0.1f;
        box_object.width = 0.2f;
        box_object.height = 0.2f;
        if(detect_collision(box_character, box_object, 0)){
            switch(coins[i].type){
                case 0: character.yellow_coins_collected++; break;
                case 1: character.black_coins_collected++; break;
                case 2: character.green_coins_collected++; break;
            }
            coins[i].position.x = -500.0f;
            coins[i].position.y = -500.0f;
        }
    }
}

// Collision with enemy 1
void detect_collision_with_enemy1() {
    for (int i = 0; i < number_of_enemy1; i++) {
        box_object.x = enemy1[i].position.x;
        box_object.y = enemy1[i].position.y - 0.05f;
        box_object.width = 1.0f;
        box_object.height = 0.1f;
        if(detect_collision(box_character, box_object, enemy1[i].rotation * M_PI / 180.0f)){
            if(!character.ispoweredup && !character.on_ring){
                lose_life();
            }
        }
    }
}

// Collision with enemy 2
void detect_collision_with_enemy2() {
    for (int i = 0; i < number_of_enemy2; i++) {
        box_object.x = enemy2[i].position.x;
        box_object.y = enemy2[i].position.y - 0.05f;
        box_object.width = 10.0f;
        box_object.height = 0.3f;
        if(detect_collision(box_character, box_object, 0)){
            if(!character.ispoweredup && !character.on_ring){
                lose_life();
            }
        }
    }
}

// Collision with enemy 3
void detect_collision_with_enemy3() {
    for (int i = 0; i < number_of_enemy3; i++) {
        box_object.x = enemy3[i].position.x;
        box_object.y = enemy3[i].position.y;
        box_object.width = 0.5f;
        box_object.height = 1.0f;
        if(detect_collision(box_character, box_object, (enemy3[i].rotation + 45.0) * M_PI / 180.0f)){
            if(!character.ispoweredup && !character.on_ring){
                lose_life();
            }
            return;
        }
        box_object.x = enemy3[i].position.x;
        box_object.y = enemy3[i].position.y;
        box_object.width = 0.5f;
        box_object.height = 1.0f;
        if(detect_collision(box_character, box_object, (enemy3[i].rotation + 315.0) * M_PI / 180.0f)){
            if(!character.ispoweredup && !character.on_ring){
                lose_life();
            }
        }
    }
}

// Distance formula
float dist(float x1, float y1, float x2, float y2){
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

// Stay on the ring till you exit
void move_on_ring(){
    if(character.position.x >= semicircularring[character.on_ring-1].position.x + 1.0){
        character.on_ring = 0;
    }
    else{
        character.position.y = 0.8 + semicircularring[character.on_ring-1].position.y - sqrt(1.0f - (semicircularring[character.on_ring-1].position.x-character.position.x)*(semicircularring[character.on_ring-1].position.x-character.position.x));
    }
}

// Stay on semi circular ring
void detect_collision_with_semicircularring() {
    for (int i = 0; i < number_of_semicircularring; i++) {
        if(character.position.y-0.8 <= semicircularring[i].position.y){
            float DISTANCE = dist(semicircularring[i].position.x, semicircularring[i].position.y, character.position.x, character.position.y - 0.8);
            if(DISTANCE < 1.05f && DISTANCE > 0.9f){
                character.on_ring = i+1;
            }
            // DISTANCE = 0;
        }
    }
}

// Collision with ice balls
void detect_collision_with_dragonballz() {
    box_object.x = dragonballz.position.x - 0.15f;
    box_object.y = dragonballz.position.y - 0.15f;
    box_object.width = 0.3f;
    box_object.height = 0.3f;
    if(detect_collision(box_character, box_object, 0)){
        if(!character.ispoweredup && !character.on_ring){
            dragonballz.position.x = -500.0f;
            dragonballz.position.y = -500.0f;
            lose_life();
        }
    }
}

// Collecting special coins
void detect_collision_with_specialcoins() {
    for (int i = 0; i < number_of_specialcoins; i++) {
        box_object.x = specialcoins[i].position.x - 0.2f;
        box_object.y = specialcoins[i].position.y - 0.2f;
        box_object.width = 0.4f;
        box_object.height = 0.4f;
        if(detect_collision(box_character, box_object, 0)){
            character.specialcoins_collected++;
            specialcoins[i].position.x = -500.0f;
            specialcoins[i].position.y = -500.0f;
        }
    }
}

// Collecting extra life
void detect_collision_with_extralives() {
    for (int i = 0; i < number_of_extralives; i++) {
        box_object.x = extralives[i].position.x - 0.2f;
        box_object.y = extralives[i].position.y - 0.3f;
        box_object.width = 0.4f;
        box_object.height = 0.4f;
        if(detect_collision(box_character, box_object, 0)){
            character.lives++;
            extralives[i].position.x = -500.0f;
            extralives[i].position.y = -500.0f;
        }
    }
}

// Collecting shield
void detect_collision_with_shields() {
    for (int i = 0; i < number_of_shields; i++) {
        box_object.x = shield[i].position.x - 0.2f;
        box_object.y = shield[i].position.y;
        box_object.width = 0.4f;
        box_object.height = 0.4f;
        if(detect_collision(box_character, box_object, 0)){
            powerdown_at = shield[i].position.x + 50.0f;
            character.ispoweredup = 1;
            shield[i].position.x = -500.0f;
            shield[i].position.y = -500.0f;
        }
    }
}

// Destroying enemy 1
void detect_collision_of_balloon_with_enemy1() {
    box_object2.x = waterballoon.position.x - 0.1f;
    box_object2.y = waterballoon.position.y - 0.1f;
    box_object2.width = 0.2f;
    box_object2.height = 0.2f;
    for (int i = 0; i < number_of_enemy1; i++) {
        box_object.x = enemy1[i].position.x;
        box_object.y = enemy1[i].position.y - 0.05f;
        box_object.width = 1.0f;
        box_object.height = 0.1f;
        if(detect_collision(box_object2, box_object, enemy1[i].rotation * M_PI / 180.0f)){
            character.enemieskilled++;
            enemy1[i].position.x = -500.0f;
            enemy1[i].position.y = -500.0f;
            waterballoon.position.x = -500.0f;
            waterballoon.position.y = -0.0f;
        }
    }
}

// Destroying enemy 2
void detect_collision_of_balloon_with_enemy2() {
    box_object2.x = waterballoon.position.x - 0.1f;
    box_object2.y = waterballoon.position.y - 0.1f;
    box_object2.width = 0.2f;
    box_object2.height = 0.2f;
    for (int i = 0; i < number_of_enemy2; i++) {
        box_object.x = enemy2[i].position.x;
        box_object.y = enemy2[i].position.y - 0.05f;
        box_object.width = 10.0f;
        box_object.height = 0.3f;
        if(detect_collision(box_object2, box_object, 0)){
            character.enemieskilled++;
            enemy2[i].position.x = -500.0f;
            enemy2[i].position.y = -500.0f;
            waterballoon.position.x = -500.0f;
            waterballoon.position.y = -0.0f;
        }
    }
}


void lose_life(){
    if(character.lives){
        character.lives--;
        character.position.x = -3;
        character.position.y = -3;
        camera_x = 0;
    }
    else{
        game_over();
    }
}

void game_over() {
    quit(window);
}
