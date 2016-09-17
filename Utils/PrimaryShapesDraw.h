/*
*	PrimariShapesDraw:
*	-Esse arquivo possui um enumerador responsavel por representar cores diversas no jogo.
*	-Também possui a função que permite a fácil representação opengl de um retângulo.
*/

enum Color{RED, GREEN, BLUE, ORANGE, MAGENTA, YELLOW, WHITE, BLACK};


void setDrawColor(Color c){
	switch(c){
		case RED:
			glColor3d(1,0,0);
			break;
		case GREEN:
			glColor3d(0,1,0);
			break;
		case BLUE:
			glColor3d(0,0,1);
			break;
		case ORANGE:
			glColor3d(1,0.5,0);
			break;
		case MAGENTA:
			glColor3d(1,0,1);
			break;
		case YELLOW:
			glColor3d(0,1,1);
			break;
		case WHITE:
			glColor3d(1,1,1);
			break;
		case BLACK:
			glColor3d(0,0,0);
			break;
	}
}

void drawRectangle(Point p, Dimension d, Color c){

	setDrawColor(c);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2d(p.x-(d.width/2),p.y+(d.height/2));
		glVertex2d(p.x-(d.width/2),p.y-(d.height/2));
		glVertex2d(p.x+(d.width/2),p.y+(d.height/2));
		glVertex2d(p.x+(d.width/2),p.y-(d.height/2));
	glEnd();
}
