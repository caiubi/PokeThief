#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <SOIL.h>
#include <string>
#include <cmath>

using namespace std;

#include "Models/Physics/WorldObject.h"
#include "Models/Characters/Character.h"


Character *mario;

Bounds screenBounds = {0, 960, 0, 540};
Bounds spaceBounds = {-1, 1, 1, -1};

bool throwP = false;

#include "Utils/WindowManager.h"

void init() {
    WorldObject corpo = WorldObject((Point){-1.0,0.0}, (Dimension){0.2,0.2}, "ImageResources/pokeball.png");
    mario = new Character(1, 10, 5, TRAINER, corpo);
}


void draw(){
    mario->draw();

    glColor3d(0,0,0);
    glBegin(GL_POLYGON);
    glVertex2d(-1, -0.1);
    glVertex2d(-1, -0.3);
    glVertex2d(1, -0.3);
    glVertex2d(1, -0.1);
    glEnd();
    glColor3d(1,1,1);
}


int main(void)
{
    GLFWwindow* window = windowSetup("PokeThief", screenBounds);
    double currentFrame, deltaTime, lastFrame, t = 0;
    Vector2D speedConst = (Vector2D){2, 1};
    Vector2D speed;
    double g = 1;
    double theta = M_PI/3.0;

//    cout << "ListPlot[{" << endl;
    init();
    lastFrame = currentFrame = glfwGetTime();

    while (!glfwWindowShouldClose(window)){

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        updateWindowConstraints(window, &spaceBounds);

//        cout << deltaTime << endl;
//        cout << t << endl;
        if(throwP){
            speed.x = speedConst.x * cos(theta) * deltaTime;
            speed.y = (speedConst.y * sin(theta) - g*t)* deltaTime;

            t+= deltaTime;

            if(mario->getPosition().y >= 0)
                mario->applySpeed(speed);
            else{
                throwP = false;
            }
            
        }
        draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
//    cout << "}]";
    destroyAndExit(window);
}

