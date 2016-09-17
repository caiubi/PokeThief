/*
*  ProgressBar:   
*	-Essa classe representa uma barra de carregamento.
*	-Dada uma porcentagem pct, a barra pode ser desenhada ou incrementada/decrementada em seus limites.
*	-Primeiro é desenhado um retângulo ao fundo da barra e depois outra barra menor dentro de tamanho relativo
*	à porcentagem.
*/
class ProgressBar : public WorldObject{
	private:
		double pct;
	public:
		ProgressBar(Point, Dimension, double);
		void drawAndUpdate(double);
		void shiftCharge(double);

		void setPct(double);

};

ProgressBar::ProgressBar(Point position, Dimension size, double pct) : WorldObject(position, size, -1, (Vector2D){0,0}){
	this->pct = pct;
}

void ProgressBar::setPct(double pct){
	this->pct = pct;
}


void ProgressBar::shiftCharge(double qt){
	pct += qt;
	if(pct > 100){
		pct = 100;
	}else if(pct < 0){
		pct = 0;
	}
}

void ProgressBar::drawAndUpdate(double deltaT){
	Point p = getPosition();
	Dimension d = getSize();
	Color c = RED;

	if(pct >= 0.25 && pct < 0.6)
		c = ORANGE;
	else if(pct > 0.6)
		c = GREEN;

	drawRectangle(p, d, BLACK);

	p.x -= d.width/2.0 - d.width*0.01;

	d.width = d.width*(pct)*0.98;
	d.height = d.height*0.8;

	p.x += d.width/2.0;

	drawRectangle(p, d, c);

	WorldObject::update(deltaT);
}