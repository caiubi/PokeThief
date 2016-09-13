class Trainer: public Character{
private:
	int nPokeballs;
	int active;
	bool canOscillate;
	double tPower, theta;
	WorldObject *mira;
	Point throwPosition;
	Vector2D rThetaToVector2D();
public:
	Trainer(int, int, WorldObject);
	Pokeball *throwPokeball();
	void drawAndUpdate(double);
	void increaseAngle();
	void decreaseAngle();
	void oscillatePower(double);
	bool isLeftDirection();
	bool isActive();

	void setLeftDirection(bool);
	void setActive(int);
	void setPowerOscillation(bool);
	void clearPower();
	void updateAimPos();

	double getPercentThrowPower();

};

Trainer::Trainer(int nPokeballs, int active, WorldObject body) : Character(0, 0, 0, TRAINER, body){
	this->nPokeballs = nPokeballs;
	tPower = 3;
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
		return new Pokeball(false, corpo);
	}
	return NULL;
}

Vector2D Trainer::rThetaToVector2D(){
	Vector2D vec;
	vec.x = sin(theta)*tPower;
	vec.y = cos(theta)*tPower;

	return vec;
}

void Trainer::updateAimPos(){
	Point aimPos = throwPosition;
	double tmpPower = tPower;
	tPower = 3;
	Vector2D speed = rThetaToVector2D();
	tPower = tmpPower;

	aimPos.x += speed.x/6.0;
	aimPos.y += speed.y/6.0;

	mira->setPosition(aimPos);
}

void Trainer::drawAndUpdate(double deltaT){
	WorldObject::drawAndUpdate(deltaT);

	updateAimPos();

//	Point ballPos = throwPosition;
//	Vector2D speed = rThetaToVector2D();

/*	glColor3d(0,0,0);
	glBegin(GL_LINES);
		glVertex2d(ballPos.x, ballPos.y);
		glVertex2d(mira->getPosition().x, mira->getPosition().y);
	glEnd();*/
	if(active)
		mira->drawAndUpdate(deltaT);

	if(canOscillate)
		oscillatePower(deltaT);

}

bool Trainer::isLeftDirection(){
	return getSize().width > 0;
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
