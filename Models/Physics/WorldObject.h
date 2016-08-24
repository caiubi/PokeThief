typedef struct{
	double x, y;
}Point, Vector2D;

typedef struct{
	double width, height;
}Dimension;

typedef struct{
	double left, right, top, bottom;
}Bounds;

Point scalePix(Point pix, Bounds windowScale, Bounds spaceScale){
	Point sp;
	sp.x = (((pix.x+windowScale.left)/(windowScale.right - windowScale.left))*(spaceScale.right - spaceScale.left)) + spaceScale.left;
	sp.y = -(((pix.y+windowScale.top)/(windowScale.bottom - windowScale.top))*(spaceScale.top - spaceScale.bottom)) - spaceScale.bottom;
	return sp;
}


class WorldObject{
protected:
	Point center;
	Dimension size;
	GLuint texture;
	void setTexture(GLuint texture);
	void setSize(Dimension size);

public:
	WorldObject();
	WorldObject(Point, Dimension, string);
	WorldObject(Point, Dimension, GLuint);
	void draw();
	void setPosition(Point);

	Point getPosition();
	Dimension getSize();
	GLuint getTexture();
	void applySpeed(Vector2D);
};

WorldObject::WorldObject(){
	center = (Point){0,0};
	size = (Dimension){0,0};
	texture = -1;
}

WorldObject::WorldObject(Point p, Dimension d, string imagePath){
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
}

WorldObject::WorldObject(Point p, Dimension d, GLuint texture){
	center = p;
	size = d;
	this->texture = texture;
}

void WorldObject::draw(){
//	cout << "[" << center.x << " " << center.y << "] tex:" << this->texture << endl; 
	double coords[2][4] = {
		{center.x-(size.width/2.0), center.x-(size.width/2.0), center.x+(size.width/2.0), center.x+(size.width/2.0)},
		{center.y-(size.height/2.0),center.y+(size.height/2.0), center.y-(size.height/2.0), center.y+(size.height/2.0)}
	};
	if(texture != -1){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(0, 0); glVertex3f(coords[0][0], coords[1][0],  0);
			glTexCoord2f(0, 1); glVertex3f(coords[0][1], coords[1][1],  0);
			glTexCoord2f(1, 0); glVertex3f(coords[0][2], coords[1][2],  0);
			glTexCoord2f(1, 1); glVertex3f(coords[0][3], coords[1][3],  0);
		glEnd();
		glDisable(GL_TEXTURE_2D);

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

void WorldObject::applySpeed(Vector2D vec){
	this->center.x += vec.x;
	this->center.y += vec.y;
//	cout << "{" << center.x << ", " << center.y << "}" << endl;
}