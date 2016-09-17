/*
*  Main:   
*   -É responsável pela inicialização do controlador principal do jogo, e pelo loop renderização da biblioteca GLFW
*   -Inclui o cabeçalho de todas as classes utilizadas para facilitar a utilização dos seus componentes.
*   -Inicializa as variáveis globais a serem utilizadas como unidades de dimensionamento de tempo e espaço.
*/

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

Bounds screenBounds = {0, 960, 0, 540};
Bounds spaceBounds = {-1, 1, 1, -1};

GameController *gameController;
double currentFrame, deltaTime, lastFrame, t = 0;
void drawAndUpdate(GLFWwindow*);
void updateWindowConstraints(GLFWwindow*, Bounds*);

#include "Utils/WindowManager.h"

void init() {
    gameController = new GameController(screenBounds, spaceBounds);
}


void drawAndUpdate(GLFWwindow *window){

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        updateWindowConstraints(window, &spaceBounds);

        gameController->drawMembersAndUpdate(deltaTime);

        gameController->processInput(window);
}


int main(void)
{
    srand(time(NULL));
    GLFWwindow* window = windowSetup("PokeThief", screenBounds);
    
    

    updateWindowConstraints(window, &spaceBounds);
    init();
    lastFrame = currentFrame = glfwGetTime();

    while (!glfwWindowShouldClose(window)){

        drawAndUpdate(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    destroyAndExit(window);
}

