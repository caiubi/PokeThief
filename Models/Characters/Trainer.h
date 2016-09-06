class Trainer: public Character{
private:
	int nPokeballs;
	double tPower, theta;
	Vector2D rThetaToVector2D(double, double);
public:
	Trainer(int, WorldObject);
	Pokeball *throwPokeball();
	void drawAndUpdate(double);
	void increaseAngle();
	void decreaseAngle();
	void incDecForce(bool);
};

Trainer::Trainer(int nPokeballs, WorldObject body) : Character(0, 0, 0, TRAINER, body){
	this->nPokeballs = nPokeballs;
	tPower = 2;
	theta = -M_PI/4.0;
}

Pokeball *Trainer::throwPokeball(){
	if(nPokeballs > 0){
		Point p = (Point){this->getPosition().x-0.2,this->getPosition().y+0.15};
		WorldObject corpo = WorldObject(p, (Dimension){0.1,0.1}, "ImageResources/pokeball.png", rThetaToVector2D(tPower,theta));
		return new Pokeball(false, corpo);
	}
	return NULL;
}

Vector2D Trainer::rThetaToVector2D(double r, double theta){
	Vector2D vec;
	vec.x = sin(theta)*r;
	vec.y = cos(theta)*r;

	return vec;
}


void Trainer::drawAndUpdate(double deltaT){
	WorldObject::drawAndUpdate(deltaT);

	Point ballPos = (Point){this->getPosition().x-0.2,this->getPosition().y+0.15};
	Vector2D speedConst = rThetaToVector2D(tPower,theta);

	glBegin(GL_LINES);
		glVertex2d(ballPos.x, ballPos.y);
		glVertex2d(ballPos.x + speedConst.x/4, ballPos.y + speedConst.y/4);
	glEnd();

}

void Trainer::increaseAngle(){
	if(theta < M_PI/2.0)
		theta += M_PI/90.0;
}

void Trainer::decreaseAngle(){
	if(theta > M_PI)
		theta -= M_PI/90.0;
}

void Trainer::incDecForce(bool increase){
	if(increase && tPower <= 2)
		tPower += 0.1;
	else if(!increase && tPower >= 0)
		tPower -= 0.1;		
}