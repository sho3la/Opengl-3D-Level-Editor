#pragma once
#include "../Transform.h"
#include "../Material/Material.h"

#include <vector>

enum Shape_Type
{
	CUBE,
	SPHERE,
	PLANE,
	MODELOBJ
};

// interface for shape ..
class Shape
{
public:
	virtual ~Shape() {}

	virtual void Create() = 0;

	virtual void Create(const char* filename) = 0;

	virtual void Draw(glm::mat4 VP_Matrx) = 0;

	virtual void Set_Texture(const char* albedo) = 0;

	Transform transform;

	Material* material = nullptr;

	Texture2D *Texture = nullptr;

	unsigned int VBO;

	unsigned int VAO;

	unsigned int EBO;

	bool is_selected = false;

	std::vector<float> VertNormTex;

	std::vector<unsigned int> indices;
};