#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Transform
{
	glm::vec3 position = glm::vec3(0.0f);

	glm::vec3 scale = glm::vec3(1.0f);

	float rotation_x = 0.0f;
	float rotation_y = 0.0f;
	float rotation_z = 0.0f;

	glm::mat4 Model_Matrx {1.0f};
};