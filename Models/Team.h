class Team : public Controller{
private:
	Trainer *trainer;
	Pokemon *pokemon;
	ProgressBar *bar;
	int active;
	double tempDeltaT;
	Scenario *scenario;

public:
	Team(Trainer*, PokemonID, Scenario*);
	
	Pokemon *getPokemon();
	Trainer *getTrainer();
	void drawMembersAndUpdate(double);
	void processKeyboardInput(GLFWwindow*);
	void processMouseInput(GLFWwindow*);
	void processInput(GLFWwindow*);
	void setActive(int);

};

Team::Team(Trainer *trainer, PokemonID pID, Scenario *scenario): Controller(0){
	this->trainer = trainer;
	this->scenario = scenario;
    this->pokemon = new Pokemon(pID, 100, 100, 0.111, trainer->getPosition(), trainer->getSize(), scenario);

	this->active = trainer->isActive();
	this->bar = new ProgressBar((Point) {trainer->getPosition().x, trainer->getPosition().y+ 3*trainer->getSize().height/4}, (Dimension){0.4, 0.05}, 1);
}

Pokemon *Team::getPokemon(){
	return pokemon;
}

Trainer *Team::getTrainer(){
	return trainer;
}

void Team::drawMembersAndUpdate(double deltaT){
	this->tempDeltaT = deltaT;
	if(trainer != NULL){
		trainer->drawAndUpdate(deltaT);		
	}
	if(pokemon != NULL){
		pokemon->drawAndUpdate(deltaT);
	}

	if(active){
		bar->setPct(trainer->getPercentThrowPower());
		bar->setPosition((Point) {trainer->getPosition().x, trainer->getPosition().y+ 3*trainer->getSize().height/4});
		bar->drawAndUpdate(deltaT);
	}
}

void Team::processKeyboardInput(GLFWwindow *window){
	int action = glfwGetKey(window, GLFW_KEY_UP);
	int action2 = glfwGetKey(window, GLFW_KEY_DOWN);
	int action3 = glfwGetKey(window, GLFW_KEY_RIGHT);
	int action4 = glfwGetKey(window, GLFW_KEY_LEFT);
	Point nextPos;

	if(action3 == GLFW_PRESS){
		if(trainer->isLeftDirection()){
			trainer->setLeftDirection(false);
			pokemon->setLeftDirection(false);
		}else if((pokemon->getPosition().x + (0.8*tempDeltaT)) <= scenario->getSpaceBounds().right){

			nextPos = scenario->getFloorHeightAt((double)(trainer->getPosition().x + (0.8*tempDeltaT)));
			trainer->move(0.8, nextPos.y);

			nextPos = scenario->getFloorHeightAt((double)(pokemon->getPosition().x + (0.8*tempDeltaT)));
			pokemon->move(0.8, nextPos.y, trainer->getPosition());
		}
	}

	if(action4 == GLFW_PRESS){
		if(!trainer->isLeftDirection()){
			trainer->setLeftDirection(true);
			pokemon->setLeftDirection(true);
		}else if((pokemon->getPosition().x - (0.8*tempDeltaT)) >= scenario->getSpaceBounds().left){
			nextPos = scenario->getFloorHeightAt((double)(trainer->getPosition().x - (0.8*tempDeltaT)));
			trainer->move(-0.8, nextPos.y);

			nextPos = scenario->getFloorHeightAt((double)(pokemon->getPosition().x - (0.8*tempDeltaT)));
			pokemon->move(-0.8, nextPos.y, trainer->getPosition());
		}
	}


	if (action == GLFW_PRESS)
		trainer->increaseAngle();

	if (action2 == GLFW_PRESS)
		trainer->decreaseAngle();
}

void Team::processMouseInput(GLFWwindow* window){

}

void Team::processInput(GLFWwindow* window){
	processKeyboardInput(window);
	processMouseInput(window);
}

void Team::setActive(int active){
	this->active = active;
	trainer->setActive(active);
}
