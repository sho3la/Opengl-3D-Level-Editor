#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "tiny_obj_loader.h"

/*
* this genertor main role is generating list of {verties,normals,uvs}  --> (VNT list)
* and pass it to renderer to just draw it 
*/
struct RenderElemnt
{
	std::vector<float> VNT;
	std::vector<unsigned int> indices;
	unsigned int texture_id;
	int num_vertx;
	int numTriangles;
	size_t material_id;
};

struct ModelRenderObject
{
	std::vector<RenderElemnt> meshes;
	std::map<std::string, unsigned int> textures;
};



class GeoGenerator
{
public:

	static RenderElemnt Cube();

	static RenderElemnt Sphere();

	static void Cylinder();

	static void HollowCylinder();

	static RenderElemnt Plane();

	static RenderElemnt Grid(int width, int Depth);

	static void Terrain();

	static void Volume3D();

	static ModelRenderObject Model3D(const char *filename);
};