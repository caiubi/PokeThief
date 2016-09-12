class Controller{
	protected:
		int state;
	public:
		Controller(int);
		void changeState(int state);
		int getState();

		void processInput(GLFWwindow*);
		void processKeyboardInput(GLFWwindow*);
		void processMouseInput(GLFWwindow*);
		void drawMembersAndUpdate(double);

};

Controller::Controller(int state){
	this->state = state;
}

void Controller::changeState(int state){
	this->state = state;
}

int Controller::getState(){
	return state;
}