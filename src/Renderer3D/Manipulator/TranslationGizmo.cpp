#include "Manipulator/TranslationGizmo.h"
#include "EditorCamera.h"
#include "Input.h"
#include "Selection.h"

#include <glew.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "WidgetGL3D.h"

TranslationGizmo::TranslationGizmo()
{
	Create();
}

TranslationGizmo::~TranslationGizmo()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void TranslationGizmo::Create()
{
	Vertices = { 0,0,0 , 1,0,0 };

		const char* vs = R"CODE(
	#version 330 core
	layout (location = 0) in vec3 aPos;

	uniform mat4 model;
	uniform mat4 viewprojection;

	void main()
	{
		gl_Position = viewprojection * model * vec4(aPos, 1.0f);
	}
)CODE";

	const char* fs = R"CODE(
	#version 330 core
	out vec4 FragColor;

	uniform vec4 color;
			
	void main()
	{
		FragColor = color;
	})CODE";

	Create_shader_program(shader_program, vs, fs);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices[0]) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void TranslationGizmo::Active_Axis()
{
	if (axis_selection == glm::vec3(1, 0, 0))
	{
		state = X_AXIS;
	}
	else if (axis_selection == glm::vec3(0, 1, 0))
	{
		state = Y_AXIS;
	}
	else if (axis_selection == glm::vec3(0, 0, 1))
	{
		state = Z_AXIS;
	}
	else
	{
		state = NO_AXIS;
	}
}

void TranslationGizmo::Reset_State()
{
	state = NO_AXIS;
}

void TranslationGizmo::Move(Shape* obj, glm::vec3 val)
{
	float inc = 0;
	float v = 0;
	float z = 0;

	switch (state)
	{
	case X_AXIS:
		v = glm::dot(glm::vec3(1, 0, 0), val);
		if (v > 0.1 || v < 0.1)
		{
			inc = val.x;
		}
		else
		{
			inc = val.z;
		}

		z = glm::dot( WidgetGL3D::cam.Front , glm::vec3(0,0,1));

		if(z > 0)
		{
			transform.position.x -= inc / 100;
		}
		else
		{
			transform.position.x += inc / 100;
		}

		
		obj->transform.position = transform.position;
		
		break;
	case Y_AXIS:
		transform.position.y -= val.y / 100;
		obj->transform.position = transform.position;
		break;
	case Z_AXIS:
		v = glm::dot(glm::vec3(1, 0, 0), val);
		if (v > 0.1 || v < 0.1)
		{
			inc = val.x;
		}
		else
		{
			inc = val.z;
		}

		z = glm::dot( WidgetGL3D::cam.Front , glm::vec3(1,0,0));

		if(z > 0)
		{
			transform.position.z += inc / 100;
		}
		else
		{
			transform.position.z -= inc / 100;
		}

		obj->transform.position = transform.position;
		break;
	default:
		break;
	}
}





void TranslationGizmo::TestMouseIntersection(glm::mat4 view, glm::mat4 projection)
{
	axis_selection = glm::vec3(0);

	float x = (2.0f * EditorInput::MousePosition.x) / EditorCamera::aspect_Ratio.x - 1.0f;
	float y = 1.0f - (2.0f * EditorInput::MousePosition.y) / EditorCamera::aspect_Ratio.y;
	float z = 1.0f;
	glm::vec3 ray_nds = glm::vec3(x, y, z);

	glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
	glm::vec4 ray_eye = inverse(projection) * ray_clip;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

	glm::vec4 tmp = (inverse(view) * ray_eye);
	glm::vec3 ray_wor{ tmp.x,tmp.y,tmp.z };
	// don't forget to normalise the vector at some point
	ray_wor = normalize(ray_wor);



	float intersection_distance; // Output of TestRayOBBIntersection()
	glm::vec3 aabb_min(-1.02f, -0.02f, -0.02f);
	glm::vec3 aabb_max(1.02f, 0.02f, 0.02f);

	//X-Axis
	transform.Model_Matrx = glm::mat4(1.0f);
	transform.Model_Matrx = glm::translate(transform.Model_Matrx, transform.position);
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_z), glm::vec3(0.0f, 0.0f, 1.0f));



	if (Selection::TestRayOBBIntersection(EditorCamera::Position,ray_wor,
	aabb_min,aabb_max,transform.Model_Matrx,intersection_distance))
	{
		axis_selection.x = 1;
		return;
	}

	//Y-Axis
	transform.Model_Matrx = glm::mat4(1.0f);
	transform.Model_Matrx = glm::translate(transform.Model_Matrx, transform.position);
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_z + 90.0f), glm::vec3(0.0f, 0.0f, 1.0f));


	if (Selection::TestRayOBBIntersection(EditorCamera::Position,ray_wor,
	aabb_min,aabb_max,transform.Model_Matrx,intersection_distance))
	{
		axis_selection.y = 1;
		return;
	}

	//Z-Axis
	transform.Model_Matrx = glm::mat4(1.0f);
	transform.Model_Matrx = glm::translate(transform.Model_Matrx, transform.position);
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_y + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_z), glm::vec3(0.0f, 0.0f, 1.0f));

	if (Selection::TestRayOBBIntersection(EditorCamera::Position,ray_wor,
	aabb_min,aabb_max,transform.Model_Matrx,intersection_distance))
	{
		axis_selection.z = 1;
		return;
	}
}

void TranslationGizmo::Draw(glm::mat4 VP_Matrx)
{
		glLineWidth(3.0f);
		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(VAO);
		use_shaderprogram(shader_program);

		setMat4(shader_program, "viewprojection", VP_Matrx);

		if(axis_selection == glm::vec3(1,0,0))
		{
			DrawX(true);
			DrawY();
			DrawZ();
		}
		else if(axis_selection == glm::vec3(0,1,0))
		{
			DrawX();
			DrawY(true);
			DrawZ();
		}
		else if(axis_selection == glm::vec3(0,0,1))
		{
			DrawX();
			DrawY();
			DrawZ(true);
		}
		else
		{
			DrawX();
			DrawY();
			DrawZ();
		}


		glLineWidth(1.0f);
		glEnable(GL_DEPTH_TEST);
}

////////////////////////////////////////////////////////////////////
float fct = 0.05f, fct2 = 0.83f;
const glm::vec3 orig = glm::vec3(0, 0, 0);
const glm::vec3 axis = glm::vec3(1, 0, 0);
const glm::vec3 vtx = glm::vec3(0, 1, 0);
const glm::vec3 vty = glm::vec3(0, 0, 1);
void DrawImCone()
{
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i <= 30; i++)
	{
		glm::vec3 pt;
		pt = vtx * cos(((2 * glm::pi<float>()) / 30.0f)*i)*fct;
		pt += vty * sin(((2 * glm::pi<float>()) / 30.0f)*i)*fct;
		pt += axis * fct2;
		pt += orig;
		glVertex3fv(&pt.x);
		pt = vtx * cos(((2 * glm::pi<float>()) / 30.0f)*(i + 1))*fct;
		pt += vty * sin(((2 * glm::pi<float>()) / 30.0f)*(i + 1))*fct;
		pt += axis * fct2;
		pt += orig;
		glVertex3fv(&pt.x);
		glVertex3f(orig.x + axis.x, orig.y + axis.y, orig.z + axis.z);

	}
	glEnd();
}

void TranslationGizmo::DrawX(bool is_hoverd)
{
	//X-Axis
	transform.Model_Matrx = glm::mat4(1.0f);
	transform.Model_Matrx = glm::translate(transform.Model_Matrx, transform.position);
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_z), glm::vec3(0.0f, 0.0f, 1.0f));
	//not need to scale it with object
	//transform.Model_Matrx = glm::scale(transform.Model_Matrx, transform.scale);
	setMat4(shader_program, "model", transform.Model_Matrx);

	if(is_hoverd)
	{
		setVec4(shader_program, "color", glm::vec4(1, 1, 1, 1));
	}
	else
	{
		setVec4(shader_program, "color", glm::vec4(1, 0, 0, 1));
	}

	DrawImCone();
	glDrawArrays(GL_LINE_LOOP, 0, 2);
}

void TranslationGizmo::DrawY(bool is_hoverd)
{
	//Y-Axis
	transform.Model_Matrx = glm::mat4(1.0f);
	transform.Model_Matrx = glm::translate(transform.Model_Matrx, transform.position);
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_z + 90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//not need to scale it with object
	//transform.Model_Matrx = glm::scale(transform.Model_Matrx, transform.scale);
	setMat4(shader_program, "model", transform.Model_Matrx);

	if (is_hoverd)
	{
		setVec4(shader_program, "color", glm::vec4(1, 1, 1, 1));
	}
	else
	{
		setVec4(shader_program, "color", glm::vec4(0, 1, 0, 1));
	}

	DrawImCone();
	glDrawArrays(GL_LINE_LOOP, 0, 2);
}

void TranslationGizmo::DrawZ(bool is_hoverd)
{
	//Z-Axis
	transform.Model_Matrx = glm::mat4(1.0f);
	transform.Model_Matrx = glm::translate(transform.Model_Matrx, transform.position);
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_y + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_z), glm::vec3(0.0f, 0.0f, 1.0f));
	//not need to scale it with object
	//transform.Model_Matrx = glm::scale(transform.Model_Matrx, transform.scale);
	setMat4(shader_program, "model", transform.Model_Matrx);

	if (is_hoverd)
	{
		setVec4(shader_program, "color", glm::vec4(1, 1, 1, 1));
	}
	else
	{
		setVec4(shader_program, "color", glm::vec4(0, 0, 1, 1));
	}

	DrawImCone();
	glDrawArrays(GL_LINE_LOOP, 0, 2);
}
