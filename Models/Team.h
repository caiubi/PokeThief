class Team : public Controller{
private:
	Trainer *trainer;
	Pokemon *pokemon;
	ProgressBar *bar;
	int active;

public:
	Team(Trainer*, PokemonID);
	
	Pokemon *getPokemon();
	Trainer *getTrainer();
	void drawMembersAndUpdate(double);
	void processKeyboardInput(GLFWwindow*);
	void processMouseInput(GLFWwindow*);
	void processInput(GLFWwindow*);
	void setActive(int);

};

Team::Team(Trainer *trainer, PokemonID pID): Controller(0){

	this->trainer = trainer;
    this->pokemon = new Pokemon(pID, 100, 50, 0.111, trainer->getPosition(), trainer->getSize());

	this->active = trainer->isActive();
	this->bar = new ProgressBar((Point) {trainer->getPosition().x, trainer->getPosition().y- 3*trainer->getSize().height/4}, (Dimension){0.4, 0.05}, 1);
}

Pokemon *Team::getPokemon(){
	return pokemon;
}

Trainer *Team::getTrainer(){
	return trainer;
}

void Team::drawMembersAndUpdate(double deltaT){
	if(trainer != NULL){
		trainer->drawAndUpdate(deltaT);		
	}
	if(pokemon != NULL){
		pokemon->drawAndUpdate(deltaT);
	}

	if(active){
		bar->setPct(trainer->getPercentThrowPower());
		bar->drawAndUpdate(deltaT);
	}
}

void Team::processKeyboardInput(GLFWwindow *window){
	int action = glfwGetKey(window, GLFW_KEY_UP);
	int action2 = glfwGetKey(window, GLFW_KEY_DOWN);
	int action3 = glfwGetKey(window, GLFW_KEY_RIGHT);
	int action4 = glfwGetKey(window, GLFW_KEY_LEFT);

	if(action3 == GLFW_PRESS){
		if(trainer->isLeftDirection()){
			trainer->setLeftDirection(false);
			pokemon->setLeftDirection(false);
		}
	}

	if(action4 == GLFW_PRESS){
		if(!trainer->isLeftDirection()){
			trainer->setLeftDirection(true);
			pokemon->setLeftDirection(true);
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
