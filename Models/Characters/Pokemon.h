enum PokemonID{PIKACHU, CHARMANDER};

class Pokemon: public Character{
	private:
		PokemonID id;
		Dimension relativeDistance;
		Point trainerPosition;
		bool caught;
		string getPokeImagePath(PokemonID);
		Scenario *scenario;
	public:
		Pokemon(PokemonID, int, int, double, Point, Dimension, Scenario*);

		void setLeftDirection(bool);
		bool isCaught();
		void drawAndUpdate(double);
		PokemonID getPokemonID();
		bool collidesWith(WorldObject*);
		void tryToCatch();
		int getMaxTries(int);
		void finishCatch();
};

Pokemon::Pokemon(PokemonID type, int hpMax, int hpCurrent, double width, Point position, Dimension trainerDim, Scenario *scenario) : Character(0, hpMax, hpCurrent, POKEMON,
			*(new WorldObject(position, (Dimension){((trainerDim.width > 0)?1:-1)*width, abs(width)}, getPokeImagePath(type), (Vector2D){0,0}))){
	this->caught = false;
	this->relativeDistance = trainerDim;
	this->id = type; 
	this->scenario = scenario;
	this->trainerPosition = position;
	setLeftDirection(isLeftDirection());

}

void Pokemon::setLeftDirection(bool left){

	Dimension d = getSize();
	Point p;
	if(left){
		d.width = abs(d.width);
		p.x = trainerPosition.x - abs(relativeDistance.width);
	}
	else{
		d.width = -abs(d.width);
		p.x = trainerPosition.x + abs(relativeDistance.width);
	}
	
	p = scenario->getFloorHeightAt(p.x);

	p.y += d.height/2;//trainerPosition.y - (relativeDistance.height/2 - getSize().height/2);

	setSize(d);
	setPosition(p);
}

void Pokemon::drawAndUpdate(double deltaT){
	if(!this->caught){
		WorldObject::drawAndUpdate(deltaT);
	}
}

string Pokemon::getPokeImagePath(PokemonID id){
	string path;
	switch(id){
		case PIKACHU:
			path = "ImageResources/pikachu.png";
			break;
		case CHARMANDER:
			path = "ImageResources/charmander.png";
			break;
	}

	return path;
}

bool Pokemon::isCaught(){
	return this->caught;
}

PokemonID Pokemon::getPokemonID(){
	return this->id;
}

bool Pokemon::collidesWith(WorldObject* obj){
	if(!this->caught){
		return WorldObject::collidesWith(obj);
	}else{
		return false;
	}
}

void Pokemon::tryToCatch(){
	this->caught = true;
}

int Pokemon::getMaxTries(int triesLim){
	double rPct = ((double)(rand()%100))/100.0;
	double hpPct = (double)(hpMax-hpCurrent)/(double)hpMax;
	double failRate = 1-(rPct*hpPct);
//	failRate = (failRate < 0)? 0 : ((failRate > 1)? 1 : failRate);
	cout << "failRate: " << failRate << endl;
	if(failRate >= 0.7){
		return floor(triesLim*0.3);
	}else if(failRate >= 0.5){
		return floor(triesLim*0.5);		
	}else if(failRate >= 0){
		return triesLim;		
	}else{
		return 0;
	}
}

void Pokemon::finishCatch(){
	this->caught = false;
	cout << "hpAntes: " << this->hpCurrent << endl;

	this->hpCurrent -= floor((double)hpMax*0.3);
	this->hpCurrent = (this->hpCurrent < 0)?0:hpCurrent;

	cout << "hpDepois: " << this->hpCurrent << endl;

}


