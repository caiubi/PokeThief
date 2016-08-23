typedef struct{
	double x, y;
}Point;

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
	private:
		Point center;
		Dimension size;
		GLuint texture;

	public:
		WorldObject(Point, Dimension, string);
		void draw();
		void setPosition(Point);
};

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

void WorldObject::draw(){
	double coords[2][4] = {
		{center.x-(size.width/2.0), center.x-(size.width/2.0), center.x+(size.width/2.0), center.x+(size.width/2.0)},
		{center.y-(size.height/2.0),center.y+(size.height/2.0), center.y-(size.height/2.0), center.y+(size.height/2.0)}
	};

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

void WorldObject::setPosition(Point center){
	this->center = center;
}