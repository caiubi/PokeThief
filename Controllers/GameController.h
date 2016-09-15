enum GameState{MENU_SCREEN, BATTLE_SCREEN, PAUSE_SCREEN};

class GameController: public Controller{
	private:
		BattleController *battleController;
		MenuController *menuController;

	public:
		GameController(Bounds, Bounds);
		void processKeyboardInput(GLFWwindow*);
		int processMouseInput(GLFWwindow*);
		void processInput(GLFWwindow*);
		void drawMembersAndUpdate(double);
};

GameController::GameController(Bounds screenBounds, Bounds spaceBounds) : Controller(0){
    this->battleController = new BattleController(screenBounds, spaceBounds);
	this->menuController = new MenuController(spaceBounds, screenBounds);
}

void GameController::drawMembersAndUpdate(double deltaT){
	switch(getState()){
		case MENU_SCREEN:
			menuController->drawMembersAndUpdate(deltaT);
			break;
		case BATTLE_SCREEN:
			battleController->drawMembersAndUpdate(deltaT);
			break;
	}

}

void GameController::processKeyboardInput(GLFWwindow* window){
	switch(getState()){
		case MENU_SCREEN:
			menuController->processKeyboardInput(window);
			break;
		case BATTLE_SCREEN:
			battleController->processKeyboardInput(window);
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