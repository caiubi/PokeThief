class Controller{
	protected:
		int state;
	public:
		Controller(int);
		void changeState(int state);
		int getState();

		void processKeyboardInput();
		void processMouseInput();
		void drawMembersAndUpdate(double, GLFWwindow*);

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