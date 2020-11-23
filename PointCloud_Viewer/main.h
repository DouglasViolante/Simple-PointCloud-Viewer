#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Dataset_Utils.h"
#include "Camera_Utils.h"
#include "Shader_Utils.h"

#define POINTSIZE	1.5f
#define VSYNC		1

#define WINDOW_NAME					"Point Cloud ViewPort"
#define VERTEX_SHADER_FILEPATH		"C:\\Users\\dougv\\Desktop\\PointCViewer_Root\\PointCloud_Viewer\\PointCloud_Viewer\\vertex.shader"
#define FRAGMENT_SHADER_FILEPATH	"C:\\Users\\dougv\\Desktop\\PointCViewer_Root\\PointCloud_Viewer\\PointCloud_Viewer\\fragment.shader"

bool isClockwise = false;

unsigned int shader_utils::shader;
unsigned int positionNumberIndices;

glm::mat4 mvp;
glm::mat4 Model;
glm::mat4 View;
glm::mat4 Projection;

