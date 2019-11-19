#pragma once
#include "Geomtry/Shape.h"
#include "Material/Material.h"
#include "Manipulator/TranslationGizmo.h"
#include "Manipulator/ScalingGizmo.h"

class Scene
{
public:
	Scene();

	~Scene();

	Shape* Add_Object(Shape_Type type, const char* filename = NULL);

	void Remove_Object(Shape* obj);

	void Draw(glm::mat4 ViewProjection);

	void Select_Object();

	int selectedObj_indx = -1;

	Material *_material = nullptr;

	std::vector<Shape*> elemnts;

	Manipulater* Active_Gizmo();

	Manipulater* transform_gizmos[2];
};