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
#include "Utils/PerlinNoise.h"
#include "Models/Scenarios/Scenario.h"
#include "Controllers/Controller.h"
#include "Models/Characters/Trainer.h"
#include "Models/Characters/Pokemon.h"
#include "Models/Team.h"
#include "Controllers/BattleController.h"


Pokeball *ball = NULL;
Trainer *trainer;

Bounds screenBounds = {0, 960, 0, 540};
Bounds spaceBounds = {-1, 1, 1, -1};

bool throwP = false;

double r = 2, theta = -M_PI/4;

BattleController *battleController;


#include "Utils/WindowManager.h"

void init() {
    battleController = new BattleController(screenBounds, spaceBounds);
//    ball = trainer->throwPokeball();

}

void update(){
/*    if(ball != NULL){
        if(scenario->collidesWith(ball, screenBounds)){
            ball->setSpeed((Vector2D){0,0});
        }
    }*/
}


void draw(){

    update();
}


int main(void)
{
    GLFWwindow* window = windowSetup("PokeThief", screenBounds);
    
    
    double currentFrame, deltaTime, lastFrame, t = 0;
    Vector2D speedConst, speed;
    updateWindowConstraints(window, &spaceBounds);
    init();
    lastFrame = currentFrame = glfwGetTime();

    while (!glfwWindowShouldClose(window)){

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        updateWindowConstraints(window, &spaceBounds);

/*        if(throwP){
            if(ball->isInRest()){
                ball->setSpeed(speedConst);
            }
            
        }*/
//        speedConst = rThetaToVector2D(r, theta);
        draw();
        battleController->drawMembersAndUpdate(deltaTime, window);

/*        trainer->drawAndUpdate(deltaTime);
        if(ball != NULL)
            ball->drawAndUpdate(deltaTime);
*/
        pollKeyboard(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
//    cout << "}]";
    destroyAndExit(window);
}

