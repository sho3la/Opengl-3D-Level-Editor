#pragma once
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Manipulator/Manipulater.h"

#include <QSet>

class Selection
{
public:
	static bool TestRayOBBIntersection(
		glm::vec3 ray_origin,        // Ray origin, in world space
		glm::vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
		glm::vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
		glm::vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
		glm::mat4 ModelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
		float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB
	);

	static glm::vec3 GetOpType(MovableAxis& type,glm::mat4 modmat, int mousepos_x , int mousepos_y);

};