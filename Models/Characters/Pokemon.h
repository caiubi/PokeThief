enum PokemonID{PIKACHU, CHARMANDER};

class Pokemon: public Character{
	private:
		PokemonID id;
		Dimension relativeDistance;
		Point trainerPosition;
		string getPokeImagePath(PokemonID);
	public:
		Pokemon(PokemonID, double, double, double, Point, Dimension);

		void setLeftDirection(bool);
};

Pokemon::Pokemon(PokemonID type, double hpMax, double hpCurrent, double width, Point position, Dimension trainerDim) : Character(0, hpMax, hpCurrent, POKEMON,
			*(new WorldObject(position, (Dimension){((trainerDim.width > 0)?1:-1)*width, abs(width)}, getPokeImagePath(type), (Vector2D){0,0}))){
	
	this->relativeDistance = trainerDim;
	this->id = type; 
	this->trainerPosition = position;
	setLeftDirection(isLeftDirection());

}

void Pokemon::setLeftDirection(bool left){

	Dimension d = getSize();
	Point p;
	p.y = trainerPosition.y - (relativeDistance.height/2 - getSize().height/2);
	if(left){
		d.width = abs(d.width);
		p.x = trainerPosition.x - abs(relativeDistance.width);
	}
	else{
		d.width = -abs(d.width);
		p.x = trainerPosition.x + abs(relativeDistance.width);
	}

	setSize(d);
	setPosition(p);
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

