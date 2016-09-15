enum BattleStates{CHARGING, THROWING, CATCHING, AIMING};

class BattleController: public Controller{
	private:
		Team *teams[2];
		Scenario *scenario;
		vector<Pokeball> pokeballs;
		Bounds screenBounds;
		int turn;
		ProgressBar *player1HP, *player2HP;
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
 
 	changeState(AIMING);

	this->screenBounds = screenBounds;

    scenario = new Scenario(GRASS, screenBounds, spaceBounds);
    Point p1 = scenario->getFloorHeightAt((int)(2*(screenBounds.right/3)));
    Point p2 = scenario->getFloorHeightAt((int)((screenBounds.right/3)));
    p1.y += (0.240241/2.0)+0.05;
    p2.y += (0.240241/2.0)+0.05;

    WorldObject corpo1 = WorldObject(p1,  (Dimension){0.1554,0.33633}, "ImageResources/trainer2.png", (Vector2D){0,0});
    Trainer *trainer1 = new Trainer(2, !turn, corpo1);

    WorldObject corpo2 = WorldObject(p2, (Dimension){-0.1554,0.33633}, "ImageResources/trainerGirl.png", (Vector2D){0,0});
    Trainer *trainer2 = new Trainer(2, turn, corpo2);

    teams[0] = new Team(trainer1, PIKACHU, scenario);
    teams[1] = new Team(trainer2, CHARMANDER, scenario);

	this->player1HP = new ProgressBar((Point) {spaceBounds.right/2.0, spaceBounds.top*0.8}, (Dimension){spaceBounds.right*0.8, 0.08}, 1);
	this->player2HP = new ProgressBar((Point) {spaceBounds.left/2.0, spaceBounds.top*0.8}, (Dimension){spaceBounds.right*0.8, 0.08}, 1);

}

void BattleController::drawMembersAndUpdate(double deltaT){
    scenario->draw();
	teams[0]->drawMembersAndUpdate(deltaT);
	teams[1]->drawMembersAndUpdate(deltaT);

	this->player1HP->setPct(teams[0]->getPokemon()->getHPPercent());
	this->player2HP->setPct(teams[1]->getPokemon()->getHPPercent());

	this->player1HP->drawAndUpdate(deltaT);
	this->player2HP->drawAndUpdate(deltaT);
//	teamRight->drawMembers(deltaT);

	for(int i = 0; i < pokeballs.size(); i++){
		pokeballs[i].drawAndUpdate(deltaT);
		if(!pokeballs[i].isInRest()){
	        if(scenario->collidesWith(&pokeballs[i], screenBounds)){
	            pokeballs[i].setSpeed((Vector2D){0,0});
	            teams[turn]->setActive(true);
	            changeTurn();
	            break;
	        }
	        if(pokeballs[i].collidesWith(teams[!turn]->getPokemon()) && !teams[!turn]->getPokemon()->isCaught()){

	    		changeState(CATCHING);
	            pokeballs[i].setSpeed((Vector2D){0,-1});
	            pokeballs[i].clearRotation();

	            pokeballs[i].setCatching(teams[!turn]->getPokemon());
	            break;
	        }
	    }else if(pokeballs[i].isSetToRemove()){
        	pokeballs.erase(pokeballs.begin()+i);
        	i--;
	    }
	}
}

void BattleController::processKeyboardInput(GLFWwindow *window){
	teams[turn]->processKeyboardInput(window);


	int action = glfwGetKey(window, GLFW_KEY_SPACE);

	if (action == GLFW_PRESS){
		if(!(getState() == CHARGING)){
			teams[turn]->getTrainer()->clearPower();
			changeState(CHARGING);
		}
		teams[turn]->getTrainer()->setPowerOscillation(true);
	}
	if (action == GLFW_RELEASE && (getState() == CHARGING)){
		teams[turn]->getTrainer()->setPowerOscillation(false);
		changeState(THROWING);
		Pokeball *pokeball = teams[turn]->getTrainer()->throwPokeball();
		if(pokeball != NULL){
			pokeballs.push_back(*pokeball);
			teams[turn]->setActive(false);
		}
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

