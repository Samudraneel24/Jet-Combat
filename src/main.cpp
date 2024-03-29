#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ThreeD.h"
#include "aeroplane.h"
#include "rectangle.h"
#include "hill.h"
#include "score.h"
#include "altitude.h"
#include "aim.h"
#include "compass.h"
#include "parachute.h"
#include "missile.h"
#include "detect_collision.h"
#include "bomb.h"
#include "speedometer.h"
#include "fuel.h"
#include "fuelmeter.h"
#include "enemy.h"
#include "arrow.h"
#include "cube.h"
#include "lives.h"
#include "ring.h"

using namespace std;


GLMatrices Matrices, Dashboard_matrix;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Aeroplane Plane;
Rectangle Sea;
std::vector<Hill> HillArr;
Score Sc;
Altitude Alt;
Aim A;
Compass C;
Speedometer Spd;
Fuelmeter F_meter;
std::vector<Parachute> Par_arr;
std::vector<Missile> M;
std::vector<Bomb> B;
std::vector<Fuel> F;
std::vector<int> Possible_base;
std::vector<Enemy> Enemy_arr;
Arrow arrow;
std::vector<Cube> Enemy_missile;
std::vector<Ring> Smoke_ring;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int counter = 0;
int tick_counter = 0;
int missile_interval = 0, bomb_interval = 0;
float fuel_count = 500.0;
int Cur_checkpoint = 0;
int gamewon = 0, gameover = 0;
int lives = 3;
std::vector<Life> Life_arr;

int cam_option = 1;
int no_op = 1;
int score = 0;
int Water_counter = 0;
// int altitude = 0;

float cam_theta = 0, cam_phi = 0;

float prev_time, delta_time;

float FoV = 45.0;

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
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye(3, 3, 3);
    glm::vec3 up (0, 1, 0);
    glm::vec3 target (0, 0, 0);

    if(cam_option == 1){
        // Follow_cam_view
        eye = {Plane.position.x + 10*sin(Plane.rot_y*(M_PI/180.0)), Plane.position.y + 3, Plane.position.z - 10*cos(Plane.rot_y*(M_PI/180.0))};
        up = {0, 1, 0};
        target = {Plane.position.x, Plane.position.y, Plane.position.z};
    }
    else if(cam_option == 2){
        // Top_view
        eye = {Plane.position.x, Plane.position.y + 50, Plane.position.z};
        up = {0, 0, 1};
        target = {Plane.position.x, Plane.position.y, Plane.position.z};
    }
    else if(cam_option == 3){
        // Plane_view
        eye = {Plane.position.x - 2.5*sin(Plane.rot_y*(M_PI/180.0)), Plane.position.y + 0.6, Plane.position.z + 2.5*cos(Plane.rot_y*(M_PI/180.0))};
        up = {0, 1, 0};
        target = {Plane.position.x - 50*sin(Plane.rot_y*(M_PI/180.0)), Plane.position.y, Plane.position.z + 50*cos(Plane.rot_y*(M_PI/180.0))};
    }
    else if(cam_option == 4){
        // Tower_view
        eye = {-5, 5, -5};
        up = {0, 1, 0};
        target = {Plane.position.x, Plane.position.y, Plane.position.z};
    }
    else if(cam_option == 5){
        // Helicopter_view
        float cam_x = Plane.position.x + 10*sin(cam_theta)*cos(cam_phi);
        float cam_y = Plane.position.y + 10*sin(cam_theta)*sin(cam_phi);
        float cam_z = Plane.position.z + 10*cos(cam_theta);
    	eye = {cam_x, cam_y, cam_z};
        up = {0, 1, 0};
        target = {Plane.position.x, Plane.position.y, Plane.position.z};
    }

    counter++;

    glm::vec3 d_eye (0, 0, 1);
    glm::vec3 d_target (0, 0, 0);
    glm::vec3 d_up (0, 1, 0);

    Dashboard_matrix.view = glm::lookAt(d_eye, d_target, d_up);
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for ThreeD
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 d_VP = Dashboard_matrix.projection * Dashboard_matrix.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP, d_MVP;  // MVP = Projection * View * Model

    // Scene render
    // ball1.draw(VP);
    Sea.draw(VP);
    Plane.draw(VP);
    A.draw(VP);
    for(int i = 0; i<HillArr.size(); i++)
        HillArr[i].draw(VP);
    Sc.draw(d_VP, score);
    Alt.draw(d_VP);
    C.draw(d_VP);
    for(int i = 0; i<Par_arr.size(); i++)
        Par_arr[i].draw(VP);
    for(int i=0; i<M.size(); i++)
        M[i].draw(VP);
    for(int i=0; i<B.size(); i++)
        B[i].draw(VP);
    Spd.draw(d_VP);
    for(int i = 0; i < F.size(); i++)
        F[i].draw(VP);
    F_meter.draw(d_VP);
    Enemy_arr[Cur_checkpoint].draw(VP);
    arrow.draw(VP);
    for(int i = 0; i < Enemy_missile.size(); i++)
        Enemy_missile[i].draw(VP);
    for(int i = 0; i < lives; i++)
        Life_arr[i].draw(d_VP);
    for(int i = 0; i < Smoke_ring.size(); i++)
        Smoke_ring[i].draw(VP);
}

void tick_input(GLFWwindow *window) {
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space  = glfwGetKey(window, GLFW_KEY_SPACE);
    int c = glfwGetKey(window, GLFW_KEY_C);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int f = glfwGetKey(window, GLFW_KEY_F);
    int k = glfwGetKey(window, GLFW_KEY_K);
    int i = glfwGetKey(window, GLFW_KEY_I);
    int b = glfwGetKey(window, GLFW_KEY_B);
    int scroll = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
    if(cam_option == 5){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        delta_time = glfwGetTime() - prev_time;
        if(xpos > 500 && xpos < 1000)
            cam_phi -= delta_time;
        else if(xpos < 500 && xpos > 0)
            cam_phi += delta_time;
        if(ypos > 500 && ypos < 1000)
            cam_theta -= delta_time;
        else if(ypos < 500 && ypos > 0)
            cam_theta += delta_time;
    }

    if (c && counter > 15) {
        if(cam_option == 1)
            cam_option = 2;
        else if(cam_option == 2)
            cam_option = 3;
        else if(cam_option == 3)
            cam_option = 4;
        else if(cam_option == 4)
            cam_option = 5;
        else
            cam_option = 1;
        counter = 0;
    }
    if(space && missile_interval > 15){
        missile_interval = 0;
        M.push_back(Missile(Plane.position.x, Plane.position.y, Plane.position.z, Plane.rot_y));
    }
    if(b && bomb_interval > 25){
        bomb_interval = 0;
        B.push_back(Bomb(Plane.position.x, Plane.position.y, Plane.position.z, Plane.speedxz, Plane.speedy, Plane.rot_y));
    }
    if(w)
        Plane.rot_up();
    if(i && fuel_count > 0.0)
        Plane.forward();
    if(k && fuel_count > 0.0)
        Plane.up();
    if(d){
        Plane.right();
        no_op = 0;
    }
    else if(a){
        Plane.left();
        no_op = 0;
    }
    else
        no_op = 1;

    prev_time = glfwGetTime();
}

void tick_elements() {

    bounding_box_t Plane_bound[4];
    for(int i = 0; i < 4; i++){
        Plane_bound[i].x = Plane.position.x + 1.5*sin(Plane.rot_y*(M_PI/180.0)) - (float)(i) * sin(Plane.rot_y*(M_PI/180.0));
        Plane_bound[i].y = Plane.position.y - 0.5;
        Plane_bound[i].z = Plane.position.z - 1.5*cos(Plane.rot_y*(M_PI/180.0)) + (float)(i) * cos(Plane.rot_y*(M_PI/180.0));
        Plane_bound[i].height = 1;
        Plane_bound[i].width = abs(sin(Plane.rot_y*(M_PI/180.0)));
        Plane_bound[i].length = abs(cos(Plane.rot_y*(M_PI/180.0)));
    }
    // Plane_bound.x = Plane.position.x + 1.5*sin(Plane.rot_y*(M_PI/180.0));
    // Plane_bound.y = Plane.position.y - 0.5;
    // Plane_bound.z = Plane.position.z - 1.5*cos(Plane.rot_y*(M_PI/180.0));
    // Plane_bound.height = 1;
    // Plane_bound.width = 4*sin(Plane.rot_y*(M_PI/180.0));
    // Plane_bound.length = 4*cos(Plane.rot_y*(M_PI/180.0));

    missile_interval++, bomb_interval++;
    tick_counter++;
    Plane.tick(no_op);
    Sea.tick();
    for(int i = 0; i<HillArr.size(); i++)
        HillArr[i].tick();
    Sc.tick();
    Alt.tick(Plane.position.y * 10);
    A.tick(Plane.position.x - 10*sin(Plane.rot_y*(M_PI/180.0)), Plane.position.y, Plane.position.z + 10*cos(Plane.rot_y*(M_PI/180.0)), Plane.rot_y);
    C.tick(Plane.rot_y);
    Spd.tick(Plane.speedxz);

    // Parachute
    if(counter % 25 == 0){
        float x = Plane.position.x - 100 + rand()%200;
        float y = Plane.position.y + 20;
        float z = Plane.position.z - 100 + rand()%200;
        Par_arr.push_back(Parachute(x, y, z));
    }
    for(int i = 0; i<Par_arr.size(); i++){
        int destroy = Par_arr[i].tick();
        if(destroy == 1){
            Par_arr.erase(Par_arr.begin() + i);
            i--;
        }
    }

    for(int i=0; i<M.size(); i++){
        int destroy = M[i].tick();
        if(destroy){
            M.erase(M.begin() + i);
            i--;
        }
        else{
            bounding_box_t Missile_bound;
            Missile_bound.x = M[i].position.x - 0.15;
            Missile_bound.y = M[i].position.y - 0.15;
            Missile_bound.z = M[i].position.z - 0.5;
            Missile_bound.width = 0.3;
            Missile_bound.height = 0.3;
            Missile_bound.length = 1.3;
            for(int j = 0; j<Par_arr.size(); j++){
                bounding_box_t Para_bound;
                Para_bound.x = Par_arr[j].position.x - 2.0;
                Para_bound.y = Par_arr[j].position.y - 4.0;
                Para_bound.z = Par_arr[j].position.z - 2.0;
                Para_bound.width = 4.0;
                Para_bound.height = 6.0;
                Para_bound.length = 4.0;
                if(detect_collision(Para_bound, Missile_bound)){
                    M.erase(M.begin() + i);
                    i--;
                    Par_arr.erase(Par_arr.begin() + j);
                    score += 25;
                    break;
                }
            }

            bounding_box_t Enemy_bound;
            Enemy_bound.x = Enemy_arr[Cur_checkpoint].position.x - 4.0;
            Enemy_bound.width = 8.0;
            Enemy_bound.y = Enemy_arr[Cur_checkpoint].position.y - 1.0;
            Enemy_bound.height = 3.5;
            Enemy_bound.z = Enemy_arr[Cur_checkpoint].position.z - 4.0;
            Enemy_bound.length = 8.0;
            if(detect_collision(Enemy_bound, Missile_bound))
                Enemy_arr[Cur_checkpoint].life--;
        }
    }

    for(int i=0; i<B.size(); i++){
        int destroy = B[i].tick();
        if(destroy){
            B.erase(B.begin() + i);
            i--;
        }
        else{
            bounding_box_t Bomb_bound;
            Bomb_bound.x = B[i].position.x - 0.15;
            Bomb_bound.y = B[i].position.y - 0.15;
            Bomb_bound.z = B[i].position.z - 0.5;
            Bomb_bound.width = 0.3;
            Bomb_bound.height = 0.3;
            Bomb_bound.length = 1.3;
            for(int j = 0; j<Par_arr.size(); j++){
                bounding_box_t Para_bound;
                Para_bound.x = Par_arr[j].position.x - 2.0;
                Para_bound.y = Par_arr[j].position.y - 4.0;
                Para_bound.z = Par_arr[j].position.z - 2.0;
                Para_bound.width = 4.0;
                Para_bound.height = 6.0;
                Para_bound.length = 4.0;
                if(detect_collision(Para_bound, Bomb_bound)){
                    B.erase(B.begin() + i);
                    i--;
                    Par_arr.erase(Par_arr.begin() + j);
                    score += 25;
                    break;
                }
            }
        }
    }

    for(int i = 0; i < HillArr.size(); i++){
        if(HillArr[i].type == 'v'){
            bounding_box_t Volcano_bound;
            Volcano_bound.x = HillArr[i].position.x - HillArr[i].BaseRadius;
            Volcano_bound.y = 0;
            Volcano_bound.z = HillArr[i].position.z - HillArr[i].BaseRadius;
            Volcano_bound.height = 1100;
            Volcano_bound.width = 2*HillArr[i].BaseRadius;
            Volcano_bound.length = 2*HillArr[i].BaseRadius;
            for(int j = 0; j < 4; j++){
                if(detect_collision(Volcano_bound, Plane_bound[j])){
                    lives--;
                    break;
                }
            }
        }
        else{
            bounding_box_t Hill_bound;
            Hill_bound.x = HillArr[i].position.x - HillArr[i].BaseRadius;
            Hill_bound.y = 0;
            Hill_bound.z = HillArr[i].position.z - HillArr[i].BaseRadius;
            Hill_bound.height = HillArr[i].Height;
            Hill_bound.width = 2*HillArr[i].BaseRadius;
            Hill_bound.length = 2*HillArr[i].BaseRadius;
            for(int j = 0; j < 4; j++){
                if(detect_collision(Hill_bound, Plane_bound[j])){
                    lives--;
                    break;
                }
            }
        }
    }

    for(int i = 0; i < F.size(); i++){
        F[i].tick();
        bounding_box_t Fuel_bound;
        Fuel_bound.x = F[i].position.x - F[i].radius;
        Fuel_bound.y = F[i].position.y - F[i].length/2;
        Fuel_bound.z = F[i].position.z - F[i].radius;
        Fuel_bound.height = F[i].length;
        Fuel_bound.width = Fuel_bound.length = F[i].radius*2;
        for(int j = 0; j < 4; j++){
            if(detect_collision(Fuel_bound, Plane_bound[j])){
                F.erase(F.begin() + i);
                i--;
                fuel_count = min(500.0, fuel_count + 250.0);
                break;
            }
        }
    }
    // cout<<Plane.speed<<endl;
    fuel_count -= Plane.speed;
    F_meter.tick(fuel_count);

    Enemy_arr[Cur_checkpoint].tick();
    if(Enemy_arr[Cur_checkpoint].life <= 0){
        Cur_checkpoint++;
        if(Cur_checkpoint == 3){
            gamewon = 1;
        }
    }
    if(tick_counter % 100 == 0){
        float x = Enemy_arr[Cur_checkpoint].position.x;
        float y = Enemy_arr[Cur_checkpoint].position.y;
        float z = Enemy_arr[Cur_checkpoint].position.z;
        float dest_x = Plane.position.x;
        float dest_y = Plane.position.y;
        float dest_z = Plane.position.z;
        float del_x = dest_x - x;
        float del_y = dest_y - y;
        float del_z = dest_z - z;
        float dist = sqrt(del_x*del_x + del_y*del_y + del_z*del_z);
        if(dist < 150.0){
            float speedx = (del_x*1.5)/dist;
            float speedy = (del_y*1.5)/dist;
            float speedz = (del_z*1.5)/dist;
            Enemy_missile.push_back(Cube(x, y, z, speedx, speedy, speedz));
        }
    }

    for(int i = 0; i < Enemy_missile.size(); i++){
        int destroy = Enemy_missile[i].tick();
        if(destroy == 1){
            Enemy_missile.erase(Enemy_missile.begin() + i);
            i--;
        }
        else{
            bounding_box_t Missile_bound;
            Missile_bound.x = Enemy_missile[i].position.x - 0.25;
            Missile_bound.y = Enemy_missile[i].position.y - 0.25;
            Missile_bound.z = Enemy_missile[i].position.z - 0.25;
            Missile_bound.length = Missile_bound.width = Missile_bound.height = 0.5;
            for( int j = 0; j < 4; j++){
                if(detect_collision(Missile_bound, Plane_bound[j])){
                    lives--;
                    Enemy_missile.erase(Enemy_missile.begin() + i);
                    i--;
                    break;
                }
            }

        }
    }

    Point Checkpoint, plane;
    Checkpoint.x = Enemy_arr[Cur_checkpoint].position.x;
    Checkpoint.y = Enemy_arr[Cur_checkpoint].position.y;
    Checkpoint.z = Enemy_arr[Cur_checkpoint].position.z;
    plane.x = Plane.position.x;
    plane.y = Plane.position.y;
    plane.z = Plane.position.z;
    arrow.tick(Checkpoint, plane, Plane.rot_y);

    if(Plane.position.y <= 0.0){
        Water_counter++;
        if(Water_counter > 20){
            lives = max(lives - 1, 0);
            Water_counter = 0;
        }
    }
    else
        Water_counter = 0;

    for(int i = 0; i < Smoke_ring.size(); i++)
        Smoke_ring[i].tick(Plane.rot_y);

    for(int i = 0; i < Life_arr.size(); i++)
        Life_arr[i].tick();

    if(lives == 0)
        gameover = 1;

    for(int i = 0; i < Smoke_ring.size(); i++){
        bounding_box_t Smoke_bound;
        Smoke_bound.x = Smoke_ring[i].position.x - 7.0;
        Smoke_bound.y = Smoke_ring[i].position.y - 7.0;
        Smoke_bound.z = Smoke_ring[i].position.z;
        Smoke_bound.height = Smoke_bound.width = 14.0;
        Smoke_bound.length = 0;
        for(int j = 0;j < 4; j++)
            if(detect_collision(Smoke_bound, Plane_bound[j])){
                lives = min(lives + 1, 3);
                break;
            }
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    srand(time(NULL));

    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // ball1       = Ball(0, 0, COLOR_RED);
    // C = ThreeD(50, 0, 0, 0, 0.5, 0.5, 3.0, COLOR_RED, COLOR_RED, COLOR_BLACK );

    Plane = Aeroplane(0, 4, 0);
    Point a, b, c, d;
    a.x = -500, a.y = 0, a.z = -500;
    b.x = 500, b.y = 0, b.z = -500;
    c.x = 500, c.y = 0, c.z = 500;
    d.x = -500, d.y = 0, d.z = 500;
    Sea = Rectangle(a, b, c, d, COLOR_SEABLUE);

    for(int i = -5; i< 5; i++){
        int left = i*100;
        int right = left + 100;
        for(int j = -5; j < 5; j++){
            int bottom = j*100;
            int up = bottom + 100;
            int x = left + 25 + rand()%50;
            int z = bottom + 25 + rand()%50;
            int type = rand()%10;
            if(type < 3)
                 HillArr.push_back(Hill(x, z, 'v'));
            else{
                 HillArr.push_back(Hill(x, z, 'h'));
                 if( HillArr[HillArr.size() - 1].TopRadius >= 4 )
                    Possible_base.push_back(HillArr.size() - 1);
            }
            x = left + 25 + rand()%50;
            z = bottom + 25 + rand()%50;
            int y = 10 + rand()%35;
            F.push_back(Fuel(x, y, z));
        }
    }

    for(int i = -4; i< 4; i++){
        int left = i*125;
        for(int j = -4; j <4; j++){
            int bottom = j*125;
            int x = left + 25 + rand()%50;
            int y = 15 + rand()%50;
            int z = bottom + 25 + rand()%50;
            Smoke_ring.push_back(Ring(x, y, z, COLOR_GREY));
        }
    } 

    while(1){
        if(Enemy_arr.size() == 3)
            break;
        int ind = rand() % Possible_base.size();
        int hill_ind = Possible_base[ind];
        float x = HillArr[hill_ind].position.x;
        float y = HillArr[hill_ind].Height/2 + 1.0;
        float z = HillArr[hill_ind].position.z;
        Enemy_arr.push_back(Enemy(x, y, z));
        Possible_base.erase(Possible_base.begin() + ind);
    }

    Sc = Score(-3.8, -3.5);
    Alt = Altitude(-3.8, -1.0);
    A = Aim(6);
    C = Compass(-3.0, 3.0);
    Spd = Speedometer(2.2, -3.5);
    F_meter = Fuelmeter(-2.8, -1.0);
    arrow = Arrow(10, 10, 10);
    for(int i = 0; i < 3; i++)
        Life_arr.push_back(Life(-1.0 + 0.75*(float)i, -3.5));

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Dashboard_matrix.MatrixID = glGetUniformLocation(programID, "d_MVP");


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
    int width  = 1000;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if(gamewon == 1){
            cout<<"\n\n\n\n\n\n";
            cout<<"---------------------------------------------------------\n\n\n\n";
            cout<<"\t\t\tYou Win !! !!\n\n\n\n";
            cout<<"---------------------------------------------------------\n\n\n";
            break;
        }
        if(gameover == 1){
            cout<<"\n\n\n\n\n\n";
            cout<<"---------------------------------------------------------\n\n\n\n";
            cout<<"\t\t\tGame over !!\n\n\n\n";
            cout<<"---------------------------------------------------------\n\n\n";
            break;
        }
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(glm::radians(FoV), 1.0f, 0.1f, 200.0f);
    Dashboard_matrix.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
