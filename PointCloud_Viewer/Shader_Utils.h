#pragma once
#include <GL\glew.h>
#include <string>
#include <iostream>
#include <fstream>



namespace shader_utils
{
	extern unsigned int shader;

	std::string readShaderFile(const char*);
	unsigned int shaderCompile(unsigned int, const std::string& );
	unsigned int createShaders(const std::string&, const std::string&);
}
