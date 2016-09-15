#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <SOIL.h>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

#include "Models/Physics/WorldObject.h"
#include "Models/Characters/Character.h"
#include "Utils/PerlinNoise.h"
#include "Models/Scenarios/Scenario.h"
#include "Controllers/Controller.h"
#include "Utils/PrimaryShapesDraw.h"
#include "Models/UI/ProgressBar.h"
#include "Models/Characters/Pokemon.h"
#include "Models/Item/Pokeball.h"
#include "Models/Characters/Trainer.h"
#include "Models/Team.h"
#include "Controllers/BattleController.h"
#include "Controllers/MenuController.h"
#include "Controllers/GameController.h"

Pokeball *ball = NULL;
Trainer *trainer;

Bounds screenBounds = {0, 960, 0, 540};
Bounds spaceBounds = {-1, 1, 1, -1};

bool throwP = false;

double r = 2, theta = -M_PI/4;

GameController *gameController;


#include "Utils/WindowManager.h"

void init() {
    gameController = new GameController(screenBounds, spaceBounds);
}

void update(){
    
}


void draw(){

    update();
}


int main(void)
{
    srand(time(NULL));
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
        gameController->drawMembersAndUpdate(deltaTime);

/*        trainer->drawAndUpdate(deltaTime);
        if(ball != NULL)
            ball->drawAndUpdate(deltaTime);
*/
        gameController->processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
//    cout << "}]";
    destroyAndExit(window);
}

