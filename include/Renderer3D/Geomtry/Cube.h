#pragma once
#include "Shape.h"

class Cube : public Shape
{
public:
	~Cube();

	void Create();

	void Create(const char* filename) {}

	void Draw(glm::mat4 VP_Matrx);

	void Set_Texture(const char* albedo);
};