class Team{
private:
	Trainer *trainer;
	Pokemon *pokemon;

public:
	Team(Trainer*, Pokemon*);
	
	Pokemon *getPokemon();
	Trainer *getTrainer();
	void drawMembers(double);
};

Team::Team(Trainer *trainer, Pokemon *pokemon){
	this->trainer = trainer;
	this->pokemon = pokemon;
}

Pokemon *Team::getPokemon(){
	return pokemon;
}

Trainer *Team::getTrainer(){
	return trainer;
}

void Team::drawMembers(double deltaT){
	if(trainer != NULL){
		trainer->drawAndUpdate(deltaT);		
	}
	if(pokemon != NULL){
		pokemon->drawAndUpdate(deltaT);
	}
}