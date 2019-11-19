#pragma once
#include "../Transform.h"
#include "../Material/Material.h"
#include "../Geomtry/Shape.h"

#include <vector>

enum MovableAxis
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS,
	NO_AXIS
};


class Manipulater
{
public:
	virtual ~Manipulater();

	virtual void Create() = 0;

	virtual void Draw(glm::mat4 VP_Matrx) = 0;

	virtual void TestMouseIntersection(glm::mat4 view, glm::mat4 projection) = 0;

	virtual void Active_Axis() = 0;

	virtual void Reset_State() = 0;

	virtual void Move(Shape* obj,glm::vec3 val) = 0;

	Transform transform;

	Shader shader_program;

	std::vector<float> Vertices;

	unsigned int VBO;

	unsigned int VAO;

	glm::vec3 axis_selection;

	bool is_selected = false;

	static MovableAxis state;
};
