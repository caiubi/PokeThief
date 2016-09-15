
enum CharacterType{TRAINER, POKEMON};

class Character: public WorldObject{
private:
	CharacterType type;
protected:
	int state;
	int hpMax, hpCurrent;
	void changeState(int);

public:
	Character(int, int, int, CharacterType, WorldObject);
	Character();

	int getMaxHP();
	int getCurrentHP();

	double getHPPercent();

	void setCurrentHP(int);

	CharacterType getCharacterType();
};


void Character::changeState(int state){
	this->state = state;
}


Character::Character() : WorldObject(){

}

Character::Character(int state, int hpMax, int hpCurrent, CharacterType type, WorldObject body) : WorldObject(body.getPosition(), body.getSize(), body.getTexture(), body.getSpeed()){
	this->state = state;
	this->hpMax = hpMax;
	this->hpCurrent = hpCurrent;
	this->type = type;
}

int Character::getMaxHP(){
	return this->hpMax;
}

int Character::getCurrentHP(){
	return this->hpCurrent;
}

void Character::setCurrentHP(int hpCurrent){
	this->hpCurrent = hpCurrent;
}

CharacterType Character::getCharacterType(){
	return type;
}

double Character::getHPPercent(){
	return (double)hpCurrent/(double)hpMax;
}
