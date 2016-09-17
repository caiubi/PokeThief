/*
*  Trainer:   
*	-Representa o personagem a ser controlado pelo jogador.
*	-Essa classe também controla a mira e oscila a energia com que o projétil vai ser atirado.
*	-Possui também o método move, que altera a posição do jogador relativo ao terreno em que ele 
*	se encontra.
*/

class Trainer: public Character{
private:
	int nPokeballs;
	int active;
	bool canOscillate;
	double tPower, theta;
	WorldObject *mira;
	Point throwPosition;
	Point nextPos;
	Vector2D rThetaToVector2D();
public:
	Trainer(int, int, WorldObject);
	Pokeball *throwPokeball();
	void drawAndUpdate(double);
	void increaseAngle();
	void decreaseAngle();
	void oscillatePower(double);
	bool isActive();

	void setLeftDirection(bool);
	void setActive(int);
	void setPowerOscillation(bool);

	void clearPower();
	void update(double);

	double getPercentThrowPower();

	void move(double, double);

};

Trainer::Trainer(int nPokeballs, int active, WorldObject body) : Character(0, 0, 0, TRAINER, body){
	this->nPokeballs = nPokeballs;
	tPower = 3;
	nextPos = (Point){0,0};
	canOscillate = false;
	double dir = (body.getSize().width > 0)?-1:1;
	theta = dir*M_PI/4.0;
	this->active = active;
	Vector2D aimPos = rThetaToVector2D();
	throwPosition = (Point){this->getPosition().x-0.1,this->getPosition().y+0.1};

	mira = new WorldObject(throwPosition, (Dimension){0.08,0.08}, "ImageResources/cross.png", (Vector2D){0,0});
}

Pokeball *Trainer::throwPokeball(){
	if(nPokeballs > 0 && active){
//		Point p = (Point){this->getPosition().x-0.2,this->getPosition().y+0.15};
		WorldObject corpo = WorldObject(throwPosition, (Dimension){0.08,0.08}, "ImageResources/pokeball.png", rThetaToVector2D());
		if(corpo.isInRest())
			corpo.setSpeed((Vector2D){0,-1});
		return new Pokeball(corpo);
	}
	return NULL;
}

Vector2D Trainer::rThetaToVector2D(){
	Vector2D vec;
	vec.x = sin(theta)*tPower;
	vec.y = cos(theta)*tPower;

	return vec;
}

void Trainer::update(double deltaT){
	throwPosition = (Point){this->getPosition().x-0.1,this->getPosition().y+0.1};
	Point aimPos = throwPosition;
	double tmpPower = tPower;
	tPower = 3;
	Vector2D speed = rThetaToVector2D();
	tPower = tmpPower;

	aimPos.x += speed.x/6.0;
	aimPos.y += speed.y/6.0;

	mira->setPosition(aimPos);

	if(nextPos.x != 0){
		this->center.x += nextPos.x*deltaT;
		this->center.y =  nextPos.y+(getSize().height/2.0);
		nextPos.x = 0;
	}

}

void Trainer::drawAndUpdate(double deltaT){
	WorldObject::draw();

	update(deltaT);

	if(active)
		mira->drawAndUpdate(deltaT);

	if(canOscillate)
		oscillatePower(deltaT);

}

void Trainer::setLeftDirection(bool left){
	Dimension d = getSize();
	if(left){
		d.width = abs(d.width);
		theta = -abs(theta);
	}
	else{
		d.width = -abs(d.width);
		theta = abs(theta);
	}

	setSize(d);
}

void Trainer::increaseAngle(){
	if(isLeftDirection()){
		if(theta+M_PI/90.0 <= 0)
			theta += M_PI/90.0;

	}else{
		if(theta-M_PI/90.0 >= 0)
			theta -= M_PI/90.0;

	}
}

void Trainer::decreaseAngle(){
	if(isLeftDirection()){
		if(theta-M_PI/90.0 >= -M_PI/2.0)
			theta -= M_PI/90.0;

	}else{
		if(theta+M_PI/90.0 <= M_PI/2.0)
			theta += M_PI/90.0;

	}
}

void Trainer::oscillatePower(double deltaT){
//	cout << deltaT << endl;
    if(tPower > 3)
		tPower = 0;	
	else if(tPower <= 3){
		tPower += 2*deltaT;
	    if(tPower > 3)
			tPower = 0;	
	}
}

void Trainer::setPowerOscillation(bool canOscillate){
	this->canOscillate = canOscillate;
}

double Trainer::getPercentThrowPower(){
//	cout << tPower/3.0 << endl;
	return tPower/3.0;
}

void Trainer::clearPower(){
	tPower = 0;
}

void Trainer::setActive(int active){
	this->active = active;
}

bool Trainer::isActive(){
	return active;
}

void Trainer::move(double shift, double nextY){
	nextPos = (Point){shift, nextY};
}
