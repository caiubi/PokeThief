/*
*  Battle Controller:   
*	-É o controlador responsavel por gerenciar todos os estados possíveis durante uma partida do jogo. 
*	-Possui um enumerador dos estados.
*	-No método construtor, os times são inicializados assim como os objetos correspondentes na tela.
*	-A dinâmica da partida funciona da seguinte forma: O time 1 sempre começa, e o estado do jogo é 
*	configurado para AIMING (mirar) se o jogador utiliza o teclado para se mover, então ele muda para o
*	estado WALKING, e ao carregar a pokebola o estado CHARGING é ativado. Desse modo, o objeto que referencia
*	o jogador retorna uma nova instância de pokeball à lista de objetos do tipo Pokeball. O turno só é trocado
*	quando a pokebola atinge o solo, ou quando ela quebra devido ao pokemon fugir da captura.
*/


enum BattleStates{CHARGING, WALKING, THROWING, CATCHING, AIMING, PAUSED, FINISHED};

class BattleController: public Controller{
	private:
		Team *teams[2];
		Scenario *scenario;
		vector<Pokeball> pokeballs;
		Bounds screenBounds, spaceBounds;
		int turn;
		int lastState;
		int pauseCount;
		ProgressBar *player1HP, *player2HP;
		WorldObject *pauseScreen, *gotcha;
	public:
		BattleController(Bounds, Bounds);

		void processKeyboardInput(GLFWwindow*);
		int processMouseInput(GLFWwindow*);
		void processInput(GLFWwindow*);
		void changeTurn();
		void drawMembersAndUpdate(double);
		void update(double);

};

BattleController::BattleController(Bounds screenBounds, Bounds spaceBounds) : Controller(0){
	turn = true;
 	lastState = -1;
 	pauseCount = 0;
 	changeState(AIMING);

	this->screenBounds = screenBounds;
	this->spaceBounds = spaceBounds;

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

	pauseScreen = new WorldObject((Point){0,0}, (Dimension){(spaceBounds.right-spaceBounds.left), spaceBounds.top - spaceBounds.bottom}, "ImageResources/PauseBG.png", (Vector2D){0,0});
	gotcha = new WorldObject((Point){0,spaceBounds.top*0.5}, (Dimension){3.047*spaceBounds.top/3.0, spaceBounds.top/3.0}, "ImageResources/gotcha.png", (Vector2D){0,0});

}

void BattleController::drawMembersAndUpdate(double deltaT){
	if(getState() == PAUSED){
		deltaT = 0;
	}
    scenario->draw();
	teams[0]->drawMembersAndUpdate(deltaT);
	teams[1]->drawMembersAndUpdate(deltaT);

	this->player1HP->setPct(teams[0]->getPokemon()->getHPPercent());
	this->player2HP->setPct(teams[1]->getPokemon()->getHPPercent());

	this->player1HP->drawAndUpdate(deltaT);
	this->player2HP->drawAndUpdate(deltaT);

	update(deltaT);

	if(getState() == PAUSED)
		this->pauseScreen->drawAndUpdate(deltaT);
	else if(getState() == FINISHED)
		this->gotcha->drawAndUpdate(deltaT);
}


void BattleController::update(double deltaT){

	for(int i = 0; i < pokeballs.size(); i++){
		pokeballs[i].drawAndUpdate(deltaT);
		if(!pokeballs[i].isInRest()){
			if(pokeballs[i].getPosition().x < spaceBounds.left || pokeballs[i].getPosition().x > spaceBounds.right){
	        	pokeballs.erase(pokeballs.begin()+i);
	            teams[turn]->setActive(true);
	            changeTurn();	        	
	            break;
			}
	        if(scenario->collidesWith(&pokeballs[i], screenBounds)){
	            pokeballs[i].setSpeed((Vector2D){0,0});
	            if(!pokeballs[i].isCatching()){
		            teams[turn]->setActive(true);
		            changeTurn();
	            }
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
            teams[turn]->setActive(true);
            changeTurn();        	
	    }else if(pokeballs[i].isCatchingSuccess()){
	    	changeState(FINISHED);
	    	break;
	    }
	}
}


void BattleController::processKeyboardInput(GLFWwindow *window){
	if(getState() != FINISHED){
		if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
			if(getState() == PAUSED && pauseCount > 30){
				changeState(lastState);
				pauseCount = 0;
			}else if(pauseCount > 30){
				lastState = getState();
				changeState(PAUSED);
				pauseCount = 0;
			}
		}
		if(pauseCount <= 30){
			pauseCount++;
		}
		if(getState() != PAUSED){
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

		}else{
			glfwGetKey(window, GLFW_KEY_SPACE);
		}		
	}

}

int BattleController::processMouseInput(GLFWwindow* window){
	return -1;
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

