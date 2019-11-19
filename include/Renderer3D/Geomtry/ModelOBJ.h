#pragma once
#include "Shape.h"

struct meshes
{
	unsigned int vbo_id = 0;
	unsigned int texture_id = 0;
	int num_vertx = 0;
	std::vector<float> VertNormTex;
	std::vector<unsigned int> indices;
};

class ModelOBJ : public Shape
{
public:
	~ModelOBJ();

	void Create() {}

	void Create(const char* filename);

	void Draw(glm::mat4 VP_Matrx);

	void Set_Texture(const char* albedo);

	std::vector<meshes> submeshes;
};