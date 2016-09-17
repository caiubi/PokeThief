/*
*  Controller:   
*	-É a classe genérica que representa uma máquina de estados controladora de renderização e processamento
*	de entrada de mouse e teclado.
*	-Como geralmente o mouse poderá mudar o estado de uma tela, então foi criado um estado neutro -1 em que
*	o estado não muda ao receber como entrada esse valor.
*/

class Controller{
	protected:
		int state;
	public:
		Controller(int);
		void changeState(int state);
		int getState();

		void processInput(GLFWwindow*);
		void processKeyboardInput(GLFWwindow*);
		int processMouseInput(GLFWwindow*);
		void drawMembersAndUpdate(double);

};

Controller::Controller(int state){
	this->state = state;
}

void Controller::changeState(int state){
	if(state != -1) 
		this->state = state;
}

int Controller::getState(){
	return state;
}