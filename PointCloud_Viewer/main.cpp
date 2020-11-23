#include "main.h"


/* User input callback */
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{	
	// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	if (key == GLFW_KEY_A && action == GLFW_REPEAT || key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		std::cout << "A Key Pressed" << std::endl;
		isClockwise = false;
		camera_utils::rotateAroundOrigin(isClockwise);
	}
	if (key == GLFW_KEY_D && action == GLFW_REPEAT || key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		std::cout << "D Key Pressed" << std::endl;
		isClockwise = true;
		camera_utils::rotateAroundOrigin(isClockwise);
	}
	if (key == GLFW_KEY_Q && action == GLFW_REPEAT || key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		std::cout << "Q Key Pressed" << std::endl;
		isClockwise = false;
		camera_utils::rotateYAxis(isClockwise);
	}
	if (key == GLFW_KEY_E && action == GLFW_REPEAT || key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		std::cout << "E Key Pressed" << std::endl;
		isClockwise = true;
		camera_utils::rotateYAxis(isClockwise);
	}
	if (key == GLFW_KEY_W && action == GLFW_REPEAT || key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		std::cout << "W Key Pressed" << std::endl;
		isClockwise = false;
		camera_utils::rotateZAxis(isClockwise);
	}
	if (key == GLFW_KEY_S && action == GLFW_REPEAT || key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		std::cout << "S Key Pressed" << std::endl;
		isClockwise = true;
		camera_utils::rotateZAxis(isClockwise);
	}
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		camera_utils::resetView();
	}
}

/* Prepare the OpenGL buffers, by binding data and attribing pointers */
void loadBuffers(const std::vector <float> vertex_position_data, const std::vector <float> vertex_color_data)
{
	//VAO
	unsigned int vertexArrayID;
	//VBO
	unsigned int vertex_bufferID;
	unsigned int color_bufferID;

	glCreateVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glCreateBuffers(1, &vertex_bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_bufferID);
	glBufferData(GL_ARRAY_BUFFER, vertex_position_data.size() * sizeof(vertex_position_data[0]), &vertex_position_data[0], GL_STATIC_DRAW);

	glCreateBuffers(1, &color_bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, color_bufferID);
	glBufferData(GL_ARRAY_BUFFER, vertex_color_data.size() * sizeof(vertex_color_data[0]), &vertex_color_data[0], GL_STATIC_DRAW);

	glEnableVertexArrayAttrib(vertexArrayID, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_bufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), 0);

	glEnableVertexArrayAttrib(vertexArrayID, 1);
	glBindBuffer(GL_ARRAY_BUFFER, color_bufferID);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

}

/* Main function */
int main(int argc, const char* argv[])
{

	std::cout << "Reading Points! Please Wait. " << std::endl;

	const std::vector <data_utils::Point_Infos> pointsInfo = data_utils::readPointsInfofromData();
	const std::vector <float> vertex_position_data		   = data_utils::getCoordinates(pointsInfo);
	const std::vector <float> vertex_color_data			   = data_utils::getPointsColor(pointsInfo);

	positionNumberIndices = 3 * vertex_position_data.size();
	std::cout << "Total Points Loaded: "	 << vertex_position_data.size() << std::endl;

	std::cout << "Read Completed! Drawing. " << std::endl;

	GLFWwindow* viewPortWindow;

	if (!glfwInit()) { return -1; }

	viewPortWindow = glfwCreateWindow(VIEWPORT_WIDTH, VIEWPORT_HEIGHT, WINDOW_NAME, NULL, NULL);

	if (!viewPortWindow)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(viewPortWindow);

	if (glewInit() != GLEW_OK){ std::cout << "Ops, Something Went Wrong! " << std::endl; }
	else{ std::cout << glGetString(GL_VERSION) << std::endl; }

	if(GLEW_ARB_direct_state_access){ std::cout << "ARB DSA Supported! " << std::endl; }

	camera_utils::computeInitialMVP_Matrix();
	loadBuffers(vertex_position_data, vertex_color_data);

	std::string vertexShader   = shader_utils::readShaderFile(VERTEX_SHADER_FILEPATH);
	std::string fragmentShader = shader_utils::readShaderFile(FRAGMENT_SHADER_FILEPATH);

	shader_utils::shader = shader_utils::createShaders(vertexShader, fragmentShader);
	glUseProgram(shader_utils::shader);

	unsigned int MatrixID = glGetUniformLocation(shader_utils::shader, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	

	glPointSize(POINTSIZE);
	glEnable(GL_DEPTH_TEST);

	glfwSwapInterval(VSYNC);
	glfwSetKeyCallback(viewPortWindow, keyCallback);
	glfwSetInputMode(viewPortWindow, GLFW_STICKY_KEYS, 1);
	glClearColor(0.690f, 0.862f, 0.890f, 0.1f);

	while (!glfwWindowShouldClose(viewPortWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glDrawArrays(GL_POINTS, 0, positionNumberIndices);

		glfwSwapBuffers(viewPortWindow);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}

