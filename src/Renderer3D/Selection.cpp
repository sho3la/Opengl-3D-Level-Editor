#include "Selection.h"
#include "WidgetGL3D.h"
#include "EditorCamera.h"

bool Selection::TestRayOBBIntersection(glm::vec3 ray_origin, glm::vec3 ray_direction, glm::vec3 aabb_min, glm::vec3 aabb_max, glm::mat4 ModelMatrix, float & intersection_distance)
{
		// Intersection method from Real-Time Rendering and Essential Mathematics for Games

	float tMin = 0.0f;
	float tMax = 100000.0f;

	glm::vec3 OBBposition_worldspace(ModelMatrix[3].x, ModelMatrix[3].y, ModelMatrix[3].z);

	glm::vec3 delta = OBBposition_worldspace - ray_origin;

	// Test intersection with the 2 planes perpendicular to the OBB's X axis
	{
		
		glm::vec3 xaxis(ModelMatrix[0].x, ModelMatrix[0].y, ModelMatrix[0].z);
		float e = glm::dot(xaxis, delta);
		float f = glm::dot(ray_direction, xaxis);

		if (fabs(f) > 0.001f) { // Standard case

			float t1 = (e + aabb_min.x) / f; // Intersection with the "left" plane
			float t2 = (e + aabb_max.x) / f; // Intersection with the "right" plane
			// t1 and t2 now contain distances betwen ray origin and ray-plane intersections

			// We want t1 to represent the nearest intersection, 
			// so if it's not the case, invert t1 and t2
			if (t1 > t2) {
				float w = t1; t1 = t2; t2 = w; // swap t1 and t2
			}

			// tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
			if (t2 < tMax)
				tMax = t2;
			// tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
			if (t1 > tMin)
				tMin = t1;

			// And here's the trick :
			// If "far" is closer than "near", then there is NO intersection.
			// See the images in the tutorials for the visual explanation.
			if (tMax < tMin)
				return false;

		}
		else { // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
			if (-e + aabb_min.x > 0.0f || -e + aabb_max.x < 0.0f)
				return false;
		}
	}


	// Test intersection with the 2 planes perpendicular to the OBB's Y axis
	// Exactly the same thing than above.
	{
		glm::vec3 yaxis(ModelMatrix[1].x, ModelMatrix[1].y, ModelMatrix[1].z);
		float e = glm::dot(yaxis, delta);
		float f = glm::dot(ray_direction, yaxis);

		if (fabs(f) > 0.001f) {

			float t1 = (e + aabb_min.y) / f;
			float t2 = (e + aabb_max.y) / f;

			if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMin > tMax)
				return false;

		}
		else {
			if (-e + aabb_min.y > 0.0f || -e + aabb_max.y < 0.0f)
				return false;
		}
	}


	// Test intersection with the 2 planes perpendicular to the OBB's Z axis
	// Exactly the same thing than above.
	{
		glm::vec3 zaxis(ModelMatrix[2].x, ModelMatrix[2].y, ModelMatrix[2].z);
		float e = glm::dot(zaxis, delta);
		float f = glm::dot(ray_direction, zaxis);

		if (fabs(f) > 0.001f) {

			float t1 = (e + aabb_min.z) / f;
			float t2 = (e + aabb_max.z) / f;

			if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMin > tMax)
				return false;

		}
		else {
			if (-e + aabb_min.z > 0.0f || -e + aabb_max.z < 0.0f)
				return false;
		}
	}

	intersection_distance = tMin;
	return true;
}


inline static glm::vec3
TransformVector(glm::vec3& v, const glm::mat4 &matrix )
{
	glm::vec3 out;

	out.x = v.x * matrix[0][0] + v.y * matrix[1][0] + v.z * matrix[2][0];
	out.y = v.x * matrix[0][1] + v.y * matrix[1][1] + v.z * matrix[2][1];
	out.z = v.x * matrix[0][2] + v.y * matrix[1][2] + v.z * matrix[2][2];

	return out;
}

inline glm::vec3 TransformPoint(const glm::vec3 &v, const glm::mat4 &matrix )
{
	glm::vec3 res;
	res.x = v.x * matrix[0][0] + v.y * matrix[1][0] + v.z * matrix[2][0] + matrix[3][0];
	res.y = v.x * matrix[0][1] + v.y * matrix[1][1] + v.z * matrix[2][1] + matrix[3][1];
	res.z = v.x * matrix[0][2] + v.y * matrix[1][2] + v.z * matrix[2][2] + matrix[3][2];
	return res;
}

inline static void 
BuildRay(int x, int y, glm::vec3 &rayOrigin, glm::vec3 &rayDir)
{
	float frameX = WidgetGL3D::cam.aspect_Ratio.x;
	float frameY = WidgetGL3D::cam.aspect_Ratio.y;
	glm::vec3 screen_space;

	glm::mat4 proj = CreateProjectionMatrix(WidgetGL3D::cam);
	glm::mat4 inv_viewmat = glm::inverse(CreateViewMatrix(WidgetGL3D::cam));
	// device space to normalized screen space
	screen_space.x = (((2.f * (float)x) / frameX) - 1) /   proj[0][0];//.right.x;
	screen_space.y = -(((2.f * (float)y) / frameY) - 1) / proj[1][1];
	screen_space.z = -1.f;

	// screen space to world space

	rayOrigin = WidgetGL3D::cam.Position;
	rayDir = TransformVector(screen_space, inv_viewmat); 
	rayDir = glm::normalize(rayDir);
}
	
inline float MathFloatAbs(const float value)
{

    if(value >= 0.0f)
    {
        return value;
    }

    return -value;

}

bool RayInter( glm::vec3 & interPoint,glm::vec4 plane,  const glm::vec3 & position, const glm::vec3 & direction)
{
	float den = glm::dot(glm::vec3{plane.x,plane.y,plane.z},direction);

	if( MathFloatAbs(den) < 0.00001 )
	{
		return false;
	}

	glm::vec3 tmp = (glm::vec3 (plane.x,plane.y,plane.z) * plane.w) - position;
	float res = (glm::dot(glm::vec3(plane.x,plane.y,plane.z),tmp) / den);
	interPoint = position + (res * direction);

	return true;

}

float ComputeScreenFactor(glm::mat4 modelmat)
{
	glm::mat4 viewproj = CreateProjectionMatrix(WidgetGL3D::cam) * CreateViewMatrix(WidgetGL3D::cam);

	glm::vec4 trf = glm::vec4(modelmat[3].x, modelmat[3].y, modelmat[3].z, 1.f);
	trf   = trf* viewproj;
	return 1.0f * 0.15f * trf.w;
}

inline static glm::vec3 
RayTrace(
	const glm::vec3& rayOrigin,
	const glm::vec3& rayDir,
	const glm::vec3& norm,
	const glm::mat4& modmat, 
	glm::vec3 trss,
	bool lockVTNorm = true)
{
	glm::vec3 df, inters;

	glm::vec3 transvec = modmat[3];
	glm::vec3  normss = glm::normalize(norm);

	glm::vec4 plane;
	plane.w =  glm::dot(transvec,normss);
	plane.x = normss.x;
	plane.y = normss.y;
	plane.z = normss.z;

	//check intersect with plane 
	RayInter(inters,plane,rayOrigin,rayDir);
	df = TransformPoint( inters, modmat );

	return df;
}


glm::vec3 Selection::GetOpType(MovableAxis& type,glm::mat4 modmat, int mousepos_x, int mousepos_y)
{
	glm::vec3 rayOrigin, rayDir, df;
	BuildRay( mousepos_x, mousepos_y, rayOrigin, rayDir);

	glm::vec3 trss = glm::vec3(1.0f);
	glm::mat4 modelmat = modmat;

	// plan 1 : X/Z
	df = RayTrace(rayOrigin, rayDir, glm::vec3(0,1,0), modelmat, trss, false);


	if ( ( df.x >= 0 ) && (df.x <= 1) && ( fabs(df.z) < 0.1f )  && (type == NO_AXIS)) { type = MovableAxis::X_AXIS; }
	else if ( ( df.z >= 0 ) && (df.z <= 1) && ( fabs(df.x) < 0.1f ) && (type == NO_AXIS)){ type = MovableAxis::Z_AXIS; }
	else
	{

	}

	return df;
}
