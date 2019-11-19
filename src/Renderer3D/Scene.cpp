#include "Scene.h"

#include "Geomtry/Sphere.h"
#include "Geomtry/Cube.h"
#include "Geomtry/Plane.h"
#include "Geomtry/ModelOBJ.h"

#include "States.h"
#include "EditorCamera.h"
#include "Input.h"
#include "Selection.h"

Scene::Scene()
{
	_material = new Material();

	transform_gizmos[0] = new TranslationGizmo();
	transform_gizmos[1] = new ScalingGizmo();
}

Scene::~Scene()
{
	delete _material;

	for (auto el : transform_gizmos)
		delete el;
}

Shape* Scene::Add_Object(Shape_Type type, const char* filename)
{
	Shape *res = nullptr;
	switch (type)
	{
	case CUBE:
		res = new Cube();
		res->Create();
		res->material = _material;
		elemnts.push_back(res);
		return res;
		break;
	case SPHERE:
		res = new Sphere();
		res->Create();
		res->material = _material;
		elemnts.push_back(res);
		return res;
		break;
	case PLANE:
		res = new Plane();
		res->Create();
		res->material = _material;
		elemnts.push_back(res);
		return res;
		break;
	case MODELOBJ:
		res = new ModelOBJ();
		res->Create(filename);
		res->material = _material;
		elemnts.push_back(res);
		return res;
		break;

	default:
		return res;
		break;
	}
}

void Scene::Remove_Object(Shape * obj)
{
}


void Scene::Draw(glm::mat4 ViewProjection)
{
	for (auto el : elemnts)
	{
		el->Draw(ViewProjection);

		if (el->is_selected)
		{
			if (Active_Gizmo()->state == NO_AXIS)
				Active_Gizmo()->TestMouseIntersection(EditorCamera::view, EditorCamera::projection);

			Active_Gizmo()->Draw(ViewProjection);
		}
	}
}

Manipulater * Scene::Active_Gizmo()
{
	switch (States::AC_Transform)
	{
	case Active_Transfromation::AC_Translation:
		return transform_gizmos[0];
		break;
	case Active_Transfromation::AC_Rotation:
		return nullptr;
		break;
	case Active_Transfromation::AC_Scale:
		return transform_gizmos[1];
		return nullptr;
		break;
	default:
		return nullptr;
		break;
	}
}

void  Scene::Select_Object()
{
	float x = (2.0f * EditorInput::MousePosition.x) / EditorCamera::aspect_Ratio.x - 1.0f;
	float y = 1.0f - (2.0f * EditorInput::MousePosition.y) / EditorCamera::aspect_Ratio.y;
	float z = 1.0f;
	glm::vec3 ray_nds = glm::vec3(x, y, z);

	glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
	glm::vec4 ray_eye = inverse(EditorCamera::projection) * ray_clip;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

	glm::vec4 tmp = (inverse(EditorCamera::view) * ray_eye);
	glm::vec3 ray_wor{ tmp.x,tmp.y,tmp.z };
	// don't forget to normalise the vector at some point
	ray_wor = normalize(ray_wor);


	// Test each each Oriented Bounding Box (OBB).
	// A physics engine can be much smarter than this, 
	// because it already has some spatial partitionning structure, 
	// like Binary Space Partitionning Tree (BSP-Tree),
	// Bounding Volume Hierarchy (BVH) or other.
	for (int i = 0; i < elemnts.size(); ++i)
	{
		float intersection_distance; // Output of TestRayOBBIntersection()
		glm::vec3 aabb_min(-elemnts[i]->transform.scale);
		glm::vec3 aabb_max(elemnts[i]->transform.scale);

		// The ModelMatrix transforms :
		// - the mesh to its desired position and orientation
		// - but also the AABB (defined with aabb_min and aabb_max) into an OBB

		if (Selection::TestRayOBBIntersection(
			EditorCamera::Position,
			ray_wor,
			aabb_min,
			aabb_max,
			elemnts[i]->transform.Model_Matrx,
			intersection_distance)
			) {
			//intersection found...
			elemnts[i]->is_selected = true;
			selectedObj_indx = i;

			Active_Gizmo()->transform = elemnts[i]->transform;

			printf("selected object indx = %i \n", selectedObj_indx);
			break;
		}
		else
		{
			selectedObj_indx = -1;
			elemnts[i]->is_selected = false;
		}
	}

}
