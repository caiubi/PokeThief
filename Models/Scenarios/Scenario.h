enum TerrainType{GRASS, SAND};

class Scenario{
private:
	Point *terrain;
	TerrainType type;
	int width;
	void generateTerrain(Bounds, Bounds);

public:
	Scenario(TerrainType type, Bounds, Bounds);
	void draw();
};

Scenario::Scenario(TerrainType type, Bounds screenBounds, Bounds spaceBounds){
	this->type = type;
	width = screenBounds.right;
    SEED = (int)(((long)time(NULL)));// << endl; 
    this->generateTerrain(screenBounds, spaceBounds);
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

void Scenario::draw(){
	int x;
	glColor3d(0,0.5,0);
	glBegin(GL_POINTS);
	for (x = 0; x < width; x++){
		glVertex2d(terrain[x].x, terrain[x].y);
	}


	glEnd();
	glColor3d(1,1,1);

}