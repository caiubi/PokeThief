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

#include "Utils/WindowManager.h"

void init() {
    WorldObject corpo = WorldObject((Point){1.0,0.09}, (Dimension){0.2222,0.240241}, "ImageResources/trainer.png", (Vector2D){0,0});
    trainer = new Trainer(2, corpo);
    ball = trainer->throwPokeball();
    scenario = new Scenario(GRASS, screenBounds, spaceBounds);

}



void draw(){
    scenario->draw();
}


int main(void)
{
    GLFWwindow* window = windowSetup("PokeThief", screenBounds);
    
    
    double currentFrame, deltaTime, lastFrame, t = 0;
    Vector2D speedConst = (Vector2D){-2, 2};
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
            }else if(ball->getPosition().y <= 0){
                speed.x /=1.5;
                speed.y /=1.5;
                if(speed.x > 0.0005 && speed.y > 0.0005){
                    ball->setSpeed(speed);
                }else{
                    speed.x = speedConst.x;
                    speed.y = speedConst.y;
                }
            }
            
        }
        trainer->drawAndUpdate(deltaTime);
        if(ball != NULL)
            ball->drawAndUpdate(deltaTime);
        draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
//    cout << "}]";
    destroyAndExit(window);
}

