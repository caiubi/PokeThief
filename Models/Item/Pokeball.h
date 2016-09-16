#define SUCCESS_OSCILLATION 12
#define MAX_TRIES 20

class Pokeball: public WorldObject{
		private:
			bool catching, catchSucess;
			double rotation;
			int oscilationCount;
			bool rotOscillationIncreasing;
			Pokemon *pokemon;
			bool remover;
			int maxTries;
		public:
			Pokeball(WorldObject);
			void update(double);
			void drawAndUpdate(double);
			void increaseRotation(double);
			void draw();
			void clearRotation();
			void oscillateRotation(double);
			void setCatching(Pokemon*);
			bool isSetToRemove();
			bool isCatching();
			bool isCatchingSuccess();
};

Pokeball::Pokeball(WorldObject body) : WorldObject(body.getPosition(), body.getSize(), body.getTexture(), body.getSpeed()){
	this->catching = false;
	this->rotation = 0;
	rotOscillationIncreasing = true;
	catchSucess = false;
	oscilationCount = 0;
	pokemon = NULL;
	remover = false;
	maxTries = MAX_TRIES;
}

void Pokeball::update(double deltaT){
	if(!isInRest() && getSpeed().x != 0){
		increaseRotation(deltaT);
	}else if(catching){
		oscillateRotation(deltaT);
	}

	WorldObject::update(deltaT);
}

void Pokeball::drawAndUpdate(double deltaT){
	draw();
	update(deltaT);
}

void Pokeball::draw(){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glTranslated(getPosition().x,getPosition().y, 0);
	glRotatef(rotation, 0.f, 0.f, 1.f); //Pra dar um efeito bacana
	glTranslated(-getPosition().x,-getPosition().y, 0);

	if(catchSucess)
		WorldObject::draw(1,0,0);
	else
		WorldObject::draw();
	glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

}

void Pokeball::setCatching(Pokemon *pokemon){
	this->catching = true;
	this->pokemon = pokemon;
	this->pokemon->tryToCatch();
	this->maxTries = this->pokemon->getMaxTries(SUCCESS_OSCILLATION);
}

bool Pokeball::isCatching(){
	return catching;
}

void Pokeball::increaseRotation(double deltaT){
	rotation += 300*deltaT;
//	cout << rotation << endl;
	if(rotation >= 360){
		rotation -= 360;
	}
}

void Pokeball::oscillateRotation(double deltaT){
	if(oscilationCount == maxTries && maxTries != SUCCESS_OSCILLATION){
		catchSucess = false;
		catching = false;
		this->remover = true;
		pokemon->finishCatch();
	}
	if(oscilationCount == SUCCESS_OSCILLATION){
		catchSucess = true;
		catching = false;
		rotation = 0;

	}
	if(rotOscillationIncreasing){
		rotation += 300*deltaT;
	}else{
		rotation -= 300*deltaT;		
	}
	if(rotation > 45 || rotation < -45){
		rotOscillationIncreasing = !rotOscillationIncreasing;
		oscilationCount++;
//		cout << oscilationCount << endl;
	}
}

void Pokeball::clearRotation(){
	rotation = 0;
}

bool Pokeball::isSetToRemove(){
	return this->remover;
}

bool Pokeball::isCatchingSuccess(){
	return this->catchSucess;
}