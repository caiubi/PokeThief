class MenuController : public Controller{
	private:
		WorldObject *startButton, *instructionsButton;
		WorldObject *background;
		Bounds spaceBounds, screenBounds;
	public:
		MenuController(Bounds, Bounds);
		void processKeyboardInput(GLFWwindow*);
		int processMouseInput(GLFWwindow*);
		void processInput(GLFWwindow*);
		void drawMembersAndUpdate(double);
};

MenuController::MenuController(Bounds spaceBounds, Bounds screenBounds) : Controller(0){
	this->spaceBounds = spaceBounds;
	this->screenBounds = screenBounds;
	background = new WorldObject((Point){0,0}, (Dimension){spaceBounds.right-spaceBounds.left, spaceBounds.top - spaceBounds.bottom}, "ImageResources/sky1.jpg", (Vector2D){0,0});

	startButton = new WorldObject((Point){0,spaceBounds.top/8.0}, (Dimension){(spaceBounds.right-spaceBounds.left)/3.0, 0.2}, "ImageResources/But2.png", (Vector2D){0,0});
	instructionsButton = new WorldObject((Point){0,-spaceBounds.top/8.0}, (Dimension){(spaceBounds.right-spaceBounds.left)/3.0, 0.2}, "ImageResources/But1.png", (Vector2D){0,0});

}

void MenuController::drawMembersAndUpdate(double deltaT){
	background->drawAndUpdate(deltaT);
	startButton->drawAndUpdate(deltaT);
	instructionsButton->drawAndUpdate(deltaT);
}

void MenuController::processKeyboardInput(GLFWwindow *window){
}

int MenuController::processMouseInput(GLFWwindow* window){
	Point mouseClick;
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS){
		glfwGetCursorPos(window, &mouseClick.x, &mouseClick.y);

		mouseClick = scalePix(mouseClick, screenBounds, spaceBounds);
		if(startButton->collidesWith(mouseClick)){
			return 1;
		}
	}
	return -1;
}

void MenuController::processInput(GLFWwindow* window){
	processKeyboardInput(window);
	processMouseInput(window);
}