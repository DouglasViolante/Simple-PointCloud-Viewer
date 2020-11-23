#include "Camera_Utils.h"



/* Compute the model view matrix projection Matrix */
void camera_utils::computeInitialMVP_Matrix()
{
	Projection = glm::perspective(glm::radians(45.f), (float) VIEWPORT_WIDTH / VIEWPORT_HEIGHT, 0.1f, 150.f);

	Model = glm::mat4(1.0f);
	//Model = glm::rotate(Model, glm::radians(45.0f), glm::vec3(0.0, 1.0f, 0.0f));

	View = glm::lookAt(
				glm::vec3(1.5f, 1.5f, 1.f), // Camera is at (4,3,3), in World Space
				glm::vec3(0, 0, 0), // and looks at the origin
				glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	mvp = Projection * View * Model;
}

/* Rotate the camera around the origin (0,0,0) */
void camera_utils::rotateAroundOrigin(const bool isClockwise)
{
	//Model = glm::mat4(1.f);
	if (isClockwise) { Model = glm::rotate(Model, glm::radians(3.141592f * 2.0f), glm::vec3(0.f, 1.f, 0.f));  }
	else			 { Model = glm::rotate(Model, glm::radians(3.141592f * 2.0f), glm::vec3(0.f, -1.f, 0.f)); }

	mvp = Projection * View * Model;

	unsigned int MatrixID = glGetUniformLocation(shader_utils::shader, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

/* At event of a pressed and released key, will rotate around Y axis */
void camera_utils::rotateYAxis(const bool isClockwise)
{
	//Model = glm::mat4(1.f);
	if (isClockwise) { Model = glm::rotate(Model, glm::radians(3.141592f * 2.0f), glm::vec3(1.f, 0.f, 0.f));  }
	else			 { Model = glm::rotate(Model, glm::radians(3.141592f * 2.0f), glm::vec3(-1.f, 0.f, 0.f)); }

	mvp = Projection * View * Model;

	unsigned int MatrixID = glGetUniformLocation(shader_utils::shader, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

/* At event of a pressed and released key, will rotate around Z axis */
void camera_utils::rotateZAxis(const bool isClockwise)
{
	//Model = glm::mat4(1.f);
	if (isClockwise) { Model = glm::rotate(Model, glm::radians(3.141592f * 2.0f), glm::vec3(0.f, 0.f, 1.f));  }
	else			 { Model = glm::rotate(Model, glm::radians(3.141592f * 2.0f), glm::vec3(0.f, 0.f, -1.f)); }

	mvp = Projection * View * Model;

	unsigned int MatrixID = glGetUniformLocation(shader_utils::shader, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

/* Reset the camera view, to it's initial state */
void camera_utils::resetView()
{
	Model = glm::mat4(1.f);

	mvp = Projection * View * Model;

	unsigned int MatrixID = glGetUniformLocation(shader_utils::shader, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}