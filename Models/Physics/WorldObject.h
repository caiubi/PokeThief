typedef struct{
	double x, y;
}Point, Vector2D;

typedef struct{
	double width, height;
}Dimension;

typedef struct{
	double left, right, top, bottom;
}Bounds;

Point scalePix(Point pix, Bounds scaleA, Bounds scaleB){
	Point pctA, scaledPix;
	double wA = scaleA.right - scaleA.left;
	double wB = scaleB.right - scaleB.left;
	double hA = scaleA.top - scaleA.bottom;
	double hB = scaleB.top - scaleB.bottom;

	pctA.x = (pix.x - scaleA.left)/wA;
	pctA.y = (pix.y - scaleA.bottom)/hA;


	scaledPix.x = (pctA.x*(wB))+scaleB.left;
	scaledPix.y = (pctA.y*(hB))+scaleB.bottom;

	return scaledPix;
}


double getTwoPointDistance(Point a, Point b){
	return sqrt(pow(b.x-a.x,2) + pow(b.y-a.y,2));
}


class WorldObject{
private:
	double time;
protected:
	Point center;
	Dimension size;
	GLuint texture;
	Vector2D speed;
	void setTexture(GLuint texture);
	void setSize(Dimension size);

public:
	static double gravityForce;
	WorldObject();
	WorldObject(Point, Dimension, string, Vector2D);
	WorldObject(Point, Dimension, GLuint, Vector2D);
	void drawAndUpdate(double);
	void draw();
	void update(double);

	void setRest();
	void setPosition(Point);
	void setSpeed(Vector2D);
//	static void setGravityForce(double)

	Point getPosition();
	Dimension getSize();
	GLuint getTexture();
	Vector2D getSpeed();
	bool isInRest();
	bool isLeftDirection();

	bool collidesWith(WorldObject*);
	bool collidesWith(Point);
};

WorldObject::WorldObject(){
	center = (Point){0,0};
	size = (Dimension){0,0};
	texture = -1;
	speed = (Vector2D) {0.0,0.0};
	time = 0;
}

WorldObject::WorldObject(Point p, Dimension d, string imagePath, Vector2D speed){
	center = p;
	size = d;
	texture = SOIL_load_OGL_texture(
		imagePath.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if (texture == 0 ) {
		cout << "Erro carregando textura: " << SOIL_last_result() << endl;
	}
	this->speed = speed;
	this->time = 0;
}

WorldObject::WorldObject(Point p, Dimension d, GLuint texture, Vector2D speed){
	center = p;
	size = d;
	this->texture = texture;
	this->speed = speed;
	this->time = 0;
}

void WorldObject::drawAndUpdate(double deltaT){
//	cout << "[" << center.x << " " << center.y << "] tex:" << this->texture << endl; 
	draw();
	update(deltaT);
}

double WorldObject::gravityForce = 2.0;

void WorldObject::draw(){
	double coords[2][4] = {
		{center.x-(size.width/2.0), center.x-(size.width/2.0), center.x+(size.width/2.0), center.x+(size.width/2.0)},
		{center.y-(size.height/2.0),center.y+(size.height/2.0), center.y-(size.height/2.0), center.y+(size.height/2.0)}
	};
	glColor3d(1,1,1);
	if(texture != -1){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(0, 0); glVertex3f(coords[0][0], coords[1][0],  0);
			glTexCoord2f(0, 1); glVertex3f(coords[0][1], coords[1][1],  0);
			glTexCoord2f(1, 0); glVertex3f(coords[0][2], coords[1][2],  0);
			glTexCoord2f(1, 1); glVertex3f(coords[0][3], coords[1][3],  0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
/*
		glColor3d(1,0,0);
 		glBegin(GL_LINE_LOOP);
			glVertex3f(coords[0][0], coords[1][0],  0);
			glVertex3f(coords[0][2], coords[1][2],  0);
			glVertex3f(coords[0][3], coords[1][3],  0);
			glVertex3f(coords[0][1], coords[1][1],  0);
		glEnd();
*/
		}
}

void WorldObject::update(double deltaT){
//	cout << "Movimento iniciado" << endl;
	Vector2D speedAux;
	double theta = M_PI/3;//atan(speed.y/speed.x);
    speedAux.x = speed.x * cos(theta);
    speedAux.y = (speed.y * sin(theta) - gravityForce*time);


	this->center.x += speedAux.x*deltaT;
	this->center.y += speedAux.y*deltaT;
	if(speed.x != 0 && speed.y != 0){
		time+=deltaT;
	}
}

void WorldObject::setPosition(Point center){
	this->center = center;
}

void WorldObject::setTexture(GLuint texture){
	this->texture = texture;
}

void WorldObject::setSize(Dimension size){
	this->size = size;
}

Point WorldObject::getPosition(){
	return this->center;
}

GLuint WorldObject::getTexture(){
	return this->texture;
}

Dimension WorldObject::getSize(){
	return this->size;
}

Vector2D WorldObject::getSpeed(){
	return this->speed;
}

void WorldObject::setSpeed(Vector2D speed){
	time = 0;
	this->speed = speed;
}

void WorldObject::setRest(){
	time = 0;
	this->speed = (Vector2D){0,0};
}

bool WorldObject::isInRest(){
	return (speed.y == 0 && speed.x == 0);
}

bool WorldObject::collidesWith(WorldObject *obj){
	return getTwoPointDistance(getPosition(), obj->getPosition()) <= getSize().width+obj->getSize().width;
 //Colisao circulo
/*	Point thisP = this->getPosition(), objP = obj->getPosition();
	Dimension thisS = this->getSize(), objS = obj->getSize();
	
	if (thisP.x-thisS.width/2.0 >= objP.x + objS.width && thisP.x + thisS.width > objP.x &&
		   thisP.y < objP.y + objS.height && thisS.height + thisP.y > objP.y) {
		return true;
	}else{
		return false;
	}*/
}

bool WorldObject::collidesWith(Point p){
//	cout << "p[" << p.x << ", " << p.y << "]" <<  endl;
	Dimension thisS = this->getSize();
	Point thisP = (Point){this->getPosition().x-(thisS.width/2), this->getPosition().y+(thisS.height/2)};
//	cout << "thisp[" << thisP.x << ", " << thisP.y << "]" <<  endl;

	if(p.x >= thisP.x && p.x <= thisP.x+thisS.width
		&& p.y <= thisP.y && p.y >= thisP.y-thisS.height){
		return true;
	}
	return false;
}

bool WorldObject::isLeftDirection(){
	return getSize().width > 0;
}

