#pragma once
#include "Shader.h"
#include "Texture2D.h"

class Material
{
public:

	Material();

	~Material();

	void Set_Textures(const char* albedo);

	void Use_Material(glm::mat4 VP_Matrx,glm::mat4 Model_Matrx);

	Texture2D *Texture = nullptr;

	Shader program;
};