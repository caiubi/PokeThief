enum GameState{MENU_SCREEN, BATTLE_SCREEN, PAUSE_SCREEN, RESTART_SCREEN, EXIT_SCREEN};

class GameController: public Controller{
	private:
		BattleController *battleController;
		MenuController *menuController;
		Bounds spaceBounds, screenBounds;
		WorldObject *sureScreen;
		int previousState;
	public:
		GameController(Bounds, Bounds);
		void processKeyboardInput(GLFWwindow*);
		int processMouseInput(GLFWwindow*);
		void processInput(GLFWwindow*);
		void drawMembersAndUpdate(double);
};

GameController::GameController(Bounds screenBounds, Bounds spaceBounds) : Controller(0){
	this->spaceBounds = spaceBounds;
	this->screenBounds = screenBounds;
    this->battleController = new BattleController(screenBounds, spaceBounds);
	this->menuController = new MenuController(spaceBounds, screenBounds);
	this->sureScreen = new WorldObject((Point){0,0}, (Dimension){(spaceBounds.right-spaceBounds.left), spaceBounds.top - spaceBounds.bottom}, "ImageResources/sure.png", (Vector2D){0,0});
	previousState = -1;
}

void GameController::drawMembersAndUpdate(double deltaT){
	switch(getState()){
		case MENU_SCREEN:
			menuController->drawMembersAndUpdate(deltaT);
			break;
		case BATTLE_SCREEN:
			battleController->drawMembersAndUpdate(deltaT);
			break;
		case RESTART_SCREEN:
			sureScreen->drawAndUpdate(deltaT);
			break;
		case EXIT_SCREEN:
			sureScreen->drawAndUpdate(deltaT);
			break;
	}


}

void GameController::processKeyboardInput(GLFWwindow* window){
	if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && getState() != RESTART_SCREEN){
	    previousState = getState();
		changeState(RESTART_SCREEN);
	}else if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && getState() != EXIT_SCREEN){
	    previousState = getState();
		changeState(EXIT_SCREEN);
	}

	if(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS){
		changeState(previousState);
	}

	switch(getState()){
		case MENU_SCREEN:
			menuController->processKeyboardInput(window);
			break;
		case BATTLE_SCREEN:
			battleController->processKeyboardInput(window);
			break;
		case RESTART_SCREEN:
			if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
			    this->battleController = new BattleController(screenBounds, spaceBounds);
			    changeState(BATTLE_SCREEN);
			}
			break;
		case EXIT_SCREEN:
			if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GL_TRUE);
			break;
	}	
}

int GameController::processMouseInput(GLFWwindow* window){
	switch(getState()){
		case MENU_SCREEN:
			changeState(menuController->processMouseInput(window));
			break;
		case BATTLE_SCREEN:
			battleController->processMouseInput(window);
			break;
	}	

	return -1;
}

void GameController::processInput(GLFWwindow* window){
	processKeyboardInput(window);
	processMouseInput(window);
}