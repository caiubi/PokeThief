class BattleController: public Controller{
	private:
		Team *teams[2];
		Scenario *scenario;
		vector<Pokeball> pokeballs;
		Bounds screenBounds;
		int turn;
		bool shootingBall;
	public:
		BattleController(Bounds, Bounds);

		void start();

		void processKeyboardInput(GLFWwindow*);
		void processMouseInput(GLFWwindow*);
		void processInput(GLFWwindow*);
		void changeTurn();
		void drawMembersAndUpdate(double);

};

BattleController::BattleController(Bounds screenBounds, Bounds spaceBounds) : Controller(0){
	turn = true;
	shootingBall = false;

	this->screenBounds = screenBounds;

    scenario = new Scenario(GRASS, screenBounds, spaceBounds);
    Point p1 = scenario->getFloorHeightAt(2*(screenBounds.right/3));
    Point p2 = scenario->getFloorHeightAt((screenBounds.right/3));
    p1.y += (0.240241/2.0)+0.05;
    p2.y += (0.240241/2.0)+0.05;

    WorldObject corpo1 = WorldObject(p1,  (Dimension){0.111,0.240241}, "ImageResources/trainer2.png", (Vector2D){0,0});
    Trainer *trainer1 = new Trainer(2, !turn, corpo1);

    WorldObject corpo2 = WorldObject(p2, (Dimension){-0.111,0.240241}, "ImageResources/trainer2.png", (Vector2D){0,0});
    Trainer *trainer2 = new Trainer(2, turn, corpo2);

    teams[0] = new Team(trainer1, NULL);
    teams[1] = new Team(trainer2, NULL);
}

void BattleController::drawMembersAndUpdate(double deltaT){
    scenario->draw();
	teams[0]->drawMembersAndUpdate(deltaT);
	teams[1]->drawMembersAndUpdate(deltaT);
//	teamRight->drawMembers(deltaT);

	for(int i = 0; i < pokeballs.size(); i++){
		pokeballs[i].drawAndUpdate(deltaT);
		if(!pokeballs[i].isInRest()){
	        if(scenario->collidesWith(&pokeballs[i], screenBounds)){
	            pokeballs[i].setSpeed((Vector2D){0,0});
	            teams[turn]->setActive(true);
	            changeTurn();
	        }
	    }
	}
}

void BattleController::processKeyboardInput(GLFWwindow *window){
	teams[turn]->processKeyboardInput(window);


	int action = glfwGetKey(window, GLFW_KEY_SPACE);

	if (action == GLFW_PRESS){
		if(!shootingBall){
			teams[turn]->getTrainer()->clearForce();
		}
		teams[turn]->getTrainer()->incDecForce();
		shootingBall = true;
	}
	if (action == GLFW_RELEASE && shootingBall){
		shootingBall = false;
		pokeballs.push_back((*teams[turn]->getTrainer()->throwPokeball()));
		teams[turn]->setActive(false);
	}
}

void BattleController::processMouseInput(GLFWwindow* window){

}

void BattleController::changeTurn(){
	turn = !turn;
	teams[0]->setActive(!turn);
	teams[1]->setActive(turn);
}

void BattleController::processInput(GLFWwindow* window){
	processKeyboardInput(window);
	processMouseInput(window);
}

