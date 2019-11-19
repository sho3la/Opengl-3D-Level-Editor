#pragma once
#include "Shape.h"

class Sphere : public Shape
{
public:
	~Sphere();

	void Create();

	void Create(const char* filename) {}

	void Draw(glm::mat4 VP_Matrx);

	void Set_Texture(const char* albedo);
};