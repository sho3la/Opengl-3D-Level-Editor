#pragma once
#include "Material/Shader.h"

class Sky
{
public:
	Sky();
	~Sky();

	void Create();

	void Draw();

	Shader _shader;
	unsigned int vao_id;
	unsigned int vbo_id;
};