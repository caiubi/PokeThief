static void error_callback(int error, const char* description)
{
	cout << description << endl;
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_T && action == GLFW_PRESS)
		throwP = true;
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Point p = scalePix((Point){xpos, ypos}, screenBounds, spaceBounds);
//	mario->setPosition(p);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
}


GLFWwindow *windowSetup(string title, Bounds screenBounds){
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	window = glfwCreateWindow(screenBounds.right, screenBounds.bottom, title.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	glClearColor(1, 1, 1, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return window;
}

void updateWindowConstraints(GLFWwindow *window, Bounds *spaceBounds){
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float) height;
	spaceBounds->left = -ratio;
	spaceBounds->right = ratio;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(spaceBounds->left, spaceBounds->right, spaceBounds->bottom, spaceBounds->top, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void destroyAndExit(GLFWwindow *window){
	glDisable(GL_BLEND);
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}