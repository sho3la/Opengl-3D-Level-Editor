#pragma once
#include "Material/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


struct SceneNavigator
{
	unsigned int SCR_WIDTH = 1920;
	unsigned int SCR_HEIGHT = 1080;

	Shader shader_program;
	Shader screenshader_program;


	unsigned int cubeVAO, cubeVBO;
	unsigned int planeVAO, planeVBO;
	unsigned int quadVAO, quadVBO;

	unsigned int Qubetexture = 0;

	glm::vec2 QuadSize = glm::vec2(60);
	glm::vec2 QuadPosition;

	unsigned int framebuffer;
	unsigned int textureColorbuffer;
	unsigned int rbo;

	int CurrentFBO_ID = 0;

	bool once = true;
};

void Create_New_SceneNavigator(SceneNavigator& self,glm::vec2 aspecRatio);

void Draw_SceneNavigator(SceneNavigator& self);