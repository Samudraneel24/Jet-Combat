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

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int counter = 0;

int cam_option = 1;
int no_op = 1;
int score = 0;
// int altitude = 0;

float cam_theta = 0, cam_phi = 0;

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
    Alt.draw(d_VP, (int)(Plane.position.y * 10));
}

void tick_input(GLFWwindow *window) {
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space  = glfwGetKey(window, GLFW_KEY_SPACE);
    int c = glfwGetKey(window, GLFW_KEY_C);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
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
    if(a)
        cam_theta -= 0.2;
    if(d)
        cam_theta += 0.2;
    if(w)
        cam_phi -= 0.2;
    if(s)
        cam_phi += 0.2;
    if(up)
        Plane.forward();
    if(right){
        Plane.right();
        no_op = 0;
    }
    else if(left){
        Plane.left();
        no_op = 0;
    }
    else
        no_op = 1;
    if(space)
        Plane.up();
}

void tick_elements() {
    // cout<<Plane.rot_y<<endl;
    Plane.tick(no_op);
    Sea.tick();
    for(int i = 0; i<HillArr.size(); i++)
        HillArr[i].tick();
    Sc.tick();
    Alt.tick();
    A.tick(Plane.position.x - 10*sin(Plane.rot_y*(M_PI/180.0)), Plane.position.y, Plane.position.z + 10*cos(Plane.rot_y*(M_PI/180.0)), Plane.rot_y);
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    srand(time(NULL));

    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // ball1       = Ball(0, 0, COLOR_RED);
    // C = ThreeD(50, 0, 0, 0, 0.5, 0.5, 3.0, COLOR_RED, COLOR_RED, COLOR_BLACK );

    Plane = Aeroplane(0, 2, 0);
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
            HillArr.push_back(Hill(x, z));
        }
    }

    Sc = Score(-3.8, -3.5);
    Alt = Altitude(-3.8, -2.8);
    A = Aim(6);

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

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    Dashboard_matrix.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
