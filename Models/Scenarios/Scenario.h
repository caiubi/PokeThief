enum TerrainType{GRASS, SAND};

class Scenario{
private:
	Point *terrain;
	TerrainType type;
	int width;
	Bounds spaceBounds;
	WorldObject *background;
	void generateTerrain(Bounds, Bounds);

public:
	Scenario(TerrainType type, Bounds, Bounds);
	Point getFloorHeightAt(int);
	void draw();
};

Scenario::Scenario(TerrainType type, Bounds screenBounds, Bounds spaceBounds){
	this->type = type;
	width = screenBounds.right;
	this->spaceBounds = spaceBounds;
    SEED = (int)(((long)time(NULL)));// << endl; 
    this->generateTerrain(screenBounds, spaceBounds);
    background = new WorldObject((Point){0,0}, (Dimension){spaceBounds.left - spaceBounds.right, spaceBounds.top - spaceBounds.bottom}, "ImageResources/sky1.jpg", (Vector2D){0,0});
}

void Scenario::generateTerrain(Bounds screenBounds, Bounds spaceBounds){
	int x, y;
	double value;
	terrain = new Point[(int)screenBounds.right];

	for (x = 0; x < screenBounds.right; x++){
		y = (int)(perlin2d(x, screenBounds.bottom/2, 0.004f, 1)*(float)(screenBounds.bottom-200))+200;
		terrain[x] = scalePix((Point){x,y}, screenBounds,spaceBounds);
	}
}

Point Scenario::getFloorHeightAt(int x){
	return terrain[x];
}

void Scenario::draw(){
	background->drawAndUpdate(0);
	int x;
	glColor3d(0,0.5,0);
	glBegin(GL_POLYGON);
	glVertex2d(spaceBounds.left, spaceBounds.bottom);
	for (x = 0; x < width; x++){
		glVertex2d(terrain[x].x, terrain[x].y);
	}
	glVertex2d(spaceBounds.right, spaceBounds.bottom);


	glEnd();
	glColor3d(1,1,1);

}