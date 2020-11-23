#include "Shader_Utils.h"


/* Used to read the shader files */
std::string shader_utils::readShaderFile(const char* filePath) 
{

	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open())
	{
		std::cerr << "Could not read shader file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();

	return content;
}

/* Compile a shader passed by params */
unsigned int shader_utils::shaderCompile(unsigned int shaderType, const std::string& source)
{
	unsigned int shader_id = glCreateShader(shaderType);
	const char* src = source.c_str();
	glShaderSource(shader_id, 1, &src, nullptr);
	glCompileShader(shader_id);

	return shader_id;
}

/* Create fragment and vertex shaders, passed by params */
unsigned int shader_utils::createShaders(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();

	unsigned int compiled_vertShader = shader_utils::shaderCompile(GL_VERTEX_SHADER,   vertexShader  );
	unsigned int compiled_fragShader = shader_utils::shaderCompile(GL_FRAGMENT_SHADER, fragmentShader);


	glAttachShader(program, compiled_vertShader);
	glAttachShader(program, compiled_fragShader);

	glLinkProgram(program);
	glValidateProgram(program);

	glDetachShader(program, compiled_vertShader);
	glDetachShader(program, compiled_fragShader);

	return program;
}