/*
*  Scenario:   
*	-Essa classe é responsavel por representar o cenário no jogo, com seu terreno e dimensionamento.
*	-Ela também trata as colisões de objetos com o seu solo.
*	-O terreno é gerado a partir da classe de ruido de perlin.
*/

enum TerrainType{GRASS, SAND};

class Scenario{
private:
	Point *terrain;
	TerrainType type;
	int width, maxY;
	GLuint terrainTexture;
	Bounds spaceBounds, screenBounds;
	WorldObject *background;
	PerlinNoise *terrainGenerator;
	void generateTerrain(Bounds, Bounds);
	void drawTerrainSegment(int, int, double);

public:
	Scenario(TerrainType type, Bounds, Bounds);
	Point getFloorHeightAt(int);
	Point getFloorHeightAt(double);
	void draw();
	bool collidesWith(WorldObject*, Bounds);
	Dimension getSize();
	Bounds getSpaceBounds();
};

Scenario::Scenario(TerrainType type, Bounds screenBounds, Bounds spaceBounds){
	this->type = type;
	this->terrainGenerator = new PerlinNoise((int)(((long)time(NULL))));
	width = screenBounds.right;
	this-> screenBounds = screenBounds;
	this->spaceBounds = spaceBounds;
    this->generateTerrain(screenBounds, spaceBounds);
    background = new WorldObject((Point){0,0}, (Dimension){spaceBounds.left - spaceBounds.right, spaceBounds.top - spaceBounds.bottom}, "ImageResources/bg2.png", (Vector2D){0,0});

    terrainTexture = SOIL_load_OGL_texture(
		"ImageResources/bg.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if (terrainTexture == 0 ) {
		cout << "Erro carregando textura: " << SOIL_last_result() << endl;
	}
	this->maxY = 0;
}

void Scenario::generateTerrain(Bounds screenBounds, Bounds spaceBounds){
	int x, y;
	double value;
	terrain = new Point[(int)screenBounds.right];

	for (x = 0; x < screenBounds.right; x++){
		y = (int)(terrainGenerator->perlin2d(x, screenBounds.bottom/2, 0.004f, 1)*(float)(screenBounds.bottom-200))+200;
		terrain[x] = scalePix((Point){x,y}, screenBounds,spaceBounds);
		if(terrain[x].y > maxY){
			maxY = terrain[x].y;
		}
	}
}

Point Scenario::getFloorHeightAt(int x){
	return terrain[x];
}

Point Scenario::getFloorHeightAt(double sx){
	int x = (scalePix((Point){sx, 0}, spaceBounds, screenBounds)).x;
	return terrain[x];
}

void Scenario::draw(){
	glColor3d(1,1,1);
	background->drawAndUpdate(0);
	int x;

	glColor3d(1,1,1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, terrainTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for(x = 0; x < width; x+=2){

		drawTerrainSegment(x, 2, spaceBounds.bottom);
		--x;
		if(x+2 >= width){
			x = (width-2);
		}

	}

	glDisable(GL_TEXTURE_2D);
	glColor3d(1,1,1);

}

void Scenario::drawTerrainSegment(int startx, int size, double yBottom){
	int x;
	glBegin(GL_TRIANGLE_FAN);
		for (x = startx; x < startx+size && x < width; x++){
			glTexCoord2f((x/(double)width), 0.243); glVertex2d(terrain[x].x, terrain[x].y);
		}
		glTexCoord2f(((--x)/(double)width), 0.183); 
		glVertex2d(terrain[x].x, terrain[x].y-0.1);
		
		glTexCoord2f(((startx)/(double)width), 0.183); 
		glVertex2d(terrain[startx].x, terrain[startx].y-0.1);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		for (x = startx; x < startx+size && x < width; x++){
			glTexCoord2f((x/(double)width), 0.183); glVertex2d(terrain[x].x, terrain[x].y-0.1);
		}
		glTexCoord2f(((--x)/(double)width), 0); 
		glVertex2d(terrain[x].x, spaceBounds.bottom);
		
		glTexCoord2f(((startx)/(double)width), 0); 
		glVertex2d(terrain[startx].x,  spaceBounds.bottom);
	glEnd();

}

bool Scenario::collidesWith(WorldObject *obj, Bounds screenBounds){
	Point pixPos = scalePix(obj->getPosition(), spaceBounds, screenBounds);

	Point startX = {obj->getPosition().x - ((obj->getSize().width)/2), 0};
	Point endX = {obj->getPosition().x + ((obj->getSize().width)/2), 0};

	startX = scalePix(startX, spaceBounds, screenBounds);
	endX = scalePix(endX, spaceBounds, screenBounds);

	bool collided = false;

	for(int x = (int)startX.x; x <= (int)(endX.x) && (x < screenBounds.right); x++){

		collided |= obj->collidesWith(terrain[x]) | (terrain[x].y > obj->getPosition().y);
		if(collided)
			break;
	}

	return collided;
}

Dimension Scenario::getSize(){
	return (Dimension){spaceBounds.right-spaceBounds.left, spaceBounds.top-spaceBounds.bottom};
}

Bounds Scenario::getSpaceBounds(){
	return spaceBounds;
}

