#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <SOIL.h>
#include <string>
#include <cmath>

using namespace std;

#include "Models/Physics/WorldObject.h"
#include "Models/Characters/Character.h"
#include "Models/Item/Pokeball.h"
#include "Models/Characters/Trainer.h"
#include "Utils/PerlinNoise.h"
#include "Models/Scenarios/Scenario.h"


Pokeball *ball = NULL;
Trainer *trainer;

Bounds screenBounds = {0, 960, 0, 540};
Bounds spaceBounds = {-1, 1, 1, -1};

bool throwP = false;

Scenario *scenario;

double r = 2, theta = -M_PI/4;

#include "Utils/WindowManager.h"

Vector2D rThetaToVector2D(double r, double theta){
    Vector2D vec;
    vec.x = sin(theta)*r;
    vec.y = cos(theta)*r;

    return vec;
}

void init() {
    Point p;
    scenario = new Scenario(GRASS, screenBounds, spaceBounds);
    p = scenario->getFloorHeightAt(2*(screenBounds.right/3));
    p.y += (0.240241/2.0)+0.05;
    WorldObject corpo = WorldObject(p, (Dimension){0.2222,0.240241}, "ImageResources/trainer.png", (Vector2D){0,0});
    trainer = new Trainer(2, corpo);
    ball = trainer->throwPokeball();

}

void update(){
    if(scenario->collidesWith(ball, screenBounds)){
        ball->setSpeed((Vector2D){0,0});

    }
}


void draw(){
    
    scenario->draw();

    Vector2D speedConst = rThetaToVector2D(r, theta); //(Vector2D){-1, 1};

    glBegin(GL_LINES);
        glVertex2d(ball->getPosition().x, ball->getPosition().y);
        glVertex2d(ball->getPosition().x + speedConst.x/4, ball->getPosition().y + speedConst.y/4);
    glEnd();
    update();
}


int main(void)
{
    GLFWwindow* window = windowSetup("PokeThief", screenBounds);
    
    
    double currentFrame, deltaTime, lastFrame, t = 0;
    Vector2D speedConst = rThetaToVector2D(r, theta); //(Vector2D){-1, 1};
    Vector2D speed = speedConst;
    updateWindowConstraints(window, &spaceBounds);
    init();
    lastFrame = currentFrame = glfwGetTime();

    while (!glfwWindowShouldClose(window)){

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        updateWindowConstraints(window, &spaceBounds);

        if(throwP){
            if(ball->isInRest()){
                ball->setSpeed(speedConst);
            }
            
        }
        speedConst = rThetaToVector2D(r, theta);
        draw();
        trainer->drawAndUpdate(deltaTime);
        if(ball != NULL)
            ball->drawAndUpdate(deltaTime);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
//    cout << "}]";
    destroyAndExit(window);
}

