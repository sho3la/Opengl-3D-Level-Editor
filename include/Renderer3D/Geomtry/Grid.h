#pragma once

#include "Shape.h"

class Grid : public Shape
{
public:
	Grid(Material* shading);
	~Grid();

	void Create();

	void Create(const char* filename) {}

	void Draw(glm::mat4 VP_Matrx);

	void Set_Texture(const char* albedo) {}

	glm::ivec2 m_gridsize;
};