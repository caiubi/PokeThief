
enum CharacterType{TRAINER, POKEMON};

class Character: public WorldObject{
private:
	int state;
	double hpMax, hpCurrent;
	CharacterType type;

protected:
	void changeState(int);

public:
	Character(int, double, double, CharacterType, WorldObject);

	double getMaxHP();
	double getCurrentHP();

	void setCurrentHP(double);

	CharacterType getCharacterType();
};


void Character::changeState(int state){
	this->state = state;
}

Character::Character(int state, double hpMax, double hpCurrent, CharacterType type, WorldObject body) : WorldObject(body.getPosition(), body.getSize(), body.getTexture()){
	this->state = state;
	this->hpMax = hpMax;
	this->hpCurrent = hpCurrent;
	this->type = type;
}

double Character::getMaxHP(){
	return this->hpMax;
}

double Character::getCurrentHP(){
	return this->hpCurrent;
}

void Character::setCurrentHP(double hpCurrent){
	this->hpCurrent = hpCurrent;
}

CharacterType Character::getCharacterType(){
	return type;
}
