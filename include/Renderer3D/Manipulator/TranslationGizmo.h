#pragma once
#include "Manipulater.h"

class TranslationGizmo : public Manipulater
{
public:
	TranslationGizmo();

	~TranslationGizmo();

	void Create();

	void Active_Axis();

	void Reset_State();

	void Move(Shape* obj,glm::vec3 val);

	void TestMouseIntersection(glm::mat4 view, glm::mat4 projection);

	void Draw(glm::mat4 VP_Matrx);

	void DrawX(bool is_hoverd = false);
	void DrawY(bool is_hoverd = false);
	void DrawZ(bool is_hoverd = false);
};