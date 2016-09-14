class Pokeball: public WorldObject{
		private:
			bool opened;
			double rotation;
		public:
			Pokeball(bool, WorldObject);
			void update(double);
			void drawAndUpdate(double);
			void increaseRotation(double);
			void draw();
			void clearRotation();
};

Pokeball::Pokeball(bool opened, WorldObject body) : WorldObject(body.getPosition(), body.getSize(), body.getTexture(), body.getSpeed()){
	this->opened = opened;
	this->rotation = 0;
}

void Pokeball::update(double deltaT){
	if(!isInRest() && getSpeed().x != 0){
		increaseRotation(deltaT);
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

	WorldObject::draw();
	glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

}

void Pokeball::increaseRotation(double deltaT){
	rotation += 300*deltaT;
//	cout << rotation << endl;
	if(rotation >= 360){
		rotation -= 360;
	}
}

void Pokeball::clearRotation(){
	rotation = 0;
}