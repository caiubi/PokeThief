#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <SOIL.h>
#include <string>

using namespace std;

#include "Models/Physics/WorldObject.h"
#include "Models/Characters/Character.h"


Character *mario;

Bounds screenBounds = {0, 960, 0, 540};
Bounds spaceBounds = {-1, 1, 1, -1};

#include "Utils/WindowManager.h"

void init() {
    WorldObject corpo = WorldObject((Point){0.0,0.0}, (Dimension){0.5,0.5}, "ImageResources/mario.png");
    mario = new Character(1, 10, 5, TRAINER, corpo);
}


void draw(){
    mario->draw();
}


int main(void)
{
    GLFWwindow* window = windowSetup("PokeThief", screenBounds);
    init();
    while (!glfwWindowShouldClose(window)){

        updateWindowConstraints(window, spaceBounds);

        draw();
//    cout << "aqui" << endl;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    destroyAndExit(window);
}

