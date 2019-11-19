#include "Geomtry/GeomtryGeneration.h"
#include "Geomtry/Sphere.h"
#include "Material/Texture2D.h"

#include <glm/glm.hpp>


RenderElemnt GeoGenerator::Cube()
{
	RenderElemnt res;
	res.VNT =
	{
		// back face
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
		// front face
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
		 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
		// left face
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
		// right face
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
		 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
		 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
		// bottom face
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
		 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
		// top face
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
		 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
	};
	return res;
}

RenderElemnt GeoGenerator::Sphere()
{
	RenderElemnt res;

	const unsigned int X_SEGMENTS = 64;
	const unsigned int Y_SEGMENTS = 64;
	const float PI = 3.14159265359f;
	for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
	{
		for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			//vertex
			res.VNT.push_back(xPos);
			res.VNT.push_back(yPos);
			res.VNT.push_back(zPos);

			//normal
			res.VNT.push_back(xPos);
			res.VNT.push_back(yPos);
			res.VNT.push_back(zPos);

			//uvs
			res.VNT.push_back(xSegment);
			res.VNT.push_back(ySegment);
		}
	}

	// indices
	//  k1--k1+1
	//  |  / |
	//  | /  |
	//  k2--k2+1
	unsigned int k1, k2;
	for (int i = 0; i < Y_SEGMENTS; ++i)
	{
		k1 = i * (X_SEGMENTS + 1);     // beginning of current stack
		k2 = k1 + X_SEGMENTS + 1;      // beginning of next stack

		for (int j = 0; j < X_SEGMENTS; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding 1st and last stacks
			if (i != 0)
			{
				// k1---k2---k1+1
				res.indices.push_back(k1);
				res.indices.push_back(k2);
				res.indices.push_back(k1 + 1);
			}

			if (i != (Y_SEGMENTS - 1))
			{
				// k1+1---k2---k2+1
				res.indices.push_back(k1 + 1);
				res.indices.push_back(k2);
				res.indices.push_back(k2 + 1);
			}

		}
	}

	return res;
}

void GeoGenerator::Cylinder()
{
}

void GeoGenerator::HollowCylinder()
{
}

RenderElemnt GeoGenerator::Plane()
{
	RenderElemnt res;

	res.VNT = {
		// positions         //normals     // texture Coords
		-1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	};

	return res;
}

RenderElemnt GeoGenerator::Grid(int width, int Depth)
{
	RenderElemnt res;

	int width_2 = width / 2;
	int depth_2 = Depth / 2;
	int i = 0;
	int count = 0;

	for (i = -width_2; i <= width_2; i++)
	{
		res.VNT.push_back((float)i);
		res.VNT.push_back(0.0f);
		res.VNT.push_back((float)-depth_2);

		res.VNT.push_back((float)i);
		res.VNT.push_back(0.0f);
		res.VNT.push_back((float)depth_2);

		res.VNT.push_back((float)-width_2);
		res.VNT.push_back(0.0f);
		res.VNT.push_back((float)i);

		res.VNT.push_back((float)width_2);
		res.VNT.push_back(0.0f);
		res.VNT.push_back((float)i);
	}

	int dw = width * Depth;
	res.indices.resize(dw);
	unsigned int* id = &res.indices[0];
	for (int i = 0; i < width*Depth; i += 4)
	{

		*id++ = i;
		*id++ = i + 1;
		*id++ = i + 2;
		*id++ = i + 3;
	}
	return res;
}

void GeoGenerator::Terrain()
{
}

void GeoGenerator::Volume3D()
{
}

///////////////////////////////////////////////////////////////////////// models loaders
inline static std::string GetBaseDir(const std::string& filepath) {
	if (filepath.find_last_of("/\\") != std::string::npos)
		return filepath.substr(0, filepath.find_last_of("/\\"));
	return "";
}

// Check if `mesh_t` contains smoothing group id.
inline static bool hasSmoothingGroup(const tinyobj::shape_t& shape)
{
	for (size_t i = 0; i < shape.mesh.smoothing_group_ids.size(); i++) {
		if (shape.mesh.smoothing_group_ids[i] > 0) {
			return true;
		}
	}
	return false;
}

inline static void CalcNormal(float N[3], float v0[3], float v1[3], float v2[3]) {
	float v10[3];
	v10[0] = v1[0] - v0[0];
	v10[1] = v1[1] - v0[1];
	v10[2] = v1[2] - v0[2];

	float v20[3];
	v20[0] = v2[0] - v0[0];
	v20[1] = v2[1] - v0[1];
	v20[2] = v2[2] - v0[2];

	N[0] = v20[1] * v10[2] - v20[2] * v10[1];
	N[1] = v20[2] * v10[0] - v20[0] * v10[2];
	N[2] = v20[0] * v10[1] - v20[1] * v10[0];

	float len2 = N[0] * N[0] + N[1] * N[1] + N[2] * N[2];
	if (len2 > 0.0f) {
		float len = sqrtf(len2);

		N[0] /= len;
		N[1] /= len;
		N[2] /= len;
	}
}

inline static void computeSmoothingNormals(const tinyobj::attrib_t& attrib, const tinyobj::shape_t& shape,
std::map<int, glm::vec3>& smoothVertexNormals) {
	smoothVertexNormals.clear();
	std::map<int, glm::vec3>::iterator iter;

	for (size_t f = 0; f < shape.mesh.indices.size() / 3; f++) {
		// Get the three indexes of the face (all faces are triangular)
		tinyobj::index_t idx0 = shape.mesh.indices[3 * f + 0];
		tinyobj::index_t idx1 = shape.mesh.indices[3 * f + 1];
		tinyobj::index_t idx2 = shape.mesh.indices[3 * f + 2];

		// Get the three vertex indexes and coordinates
		int vi[3];      // indexes
		float v[3][3];  // coordinates

		for (int k = 0; k < 3; k++) {
			vi[0] = idx0.vertex_index;
			vi[1] = idx1.vertex_index;
			vi[2] = idx2.vertex_index;
			assert(vi[0] >= 0);
			assert(vi[1] >= 0);
			assert(vi[2] >= 0);

			v[0][k] = attrib.vertices[3 * vi[0] + k];
			v[1][k] = attrib.vertices[3 * vi[1] + k];
			v[2][k] = attrib.vertices[3 * vi[2] + k];
		}

		// Compute the normal of the face
		float normal[3];
		CalcNormal(normal, v[0], v[1], v[2]);

		// Add the normal to the three vertexes
		for (size_t i = 0; i < 3; ++i) {
			iter = smoothVertexNormals.find(vi[i]);
			if (iter != smoothVertexNormals.end()) {
				// add
				iter->second.x += normal[0];
				iter->second.y += normal[1];
				iter->second.z += normal[2];
			}
			else {
				smoothVertexNormals[vi[i]].x = normal[0];
				smoothVertexNormals[vi[i]].y = normal[1];
				smoothVertexNormals[vi[i]].z = normal[2];
			}
		}

	}  // f

	// Normalize the normals, that is, make them unit vectors
	for (iter = smoothVertexNormals.begin(); iter != smoothVertexNormals.end();
		iter++) {
		iter->second = glm::normalize(iter->second);
	}

}  // computeSmoothingNormals


ModelRenderObject GeoGenerator::Model3D(const char *filename)
{
	ModelRenderObject res;

	std::string base_dir = GetBaseDir(filename);
	std::cout << "Loading " << filename << std::endl;
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename, base_dir.c_str());

	if (!warn.empty()) {
		std::cout << "WARN: " << warn << std::endl;
	}

	if (!err.empty()) {
		std::cerr << "ERR: " << err << std::endl;
	}

	if (!ret)
	{
		printf("Failed to load/parse .obj.\n");
		return ModelRenderObject{};
	}


	printf("# of vertices  = %d\n", (int)(attrib.vertices.size()) / 3);
	printf("# of normals   = %d\n", (int)(attrib.normals.size()) / 3);
	printf("# of texcoords = %d\n", (int)(attrib.texcoords.size()) / 2);
	printf("# of materials = %d\n", (int)materials.size());
	printf("# of shapes    = %d\n", (int)shapes.size());



	// Append `default` material
	materials.push_back(tinyobj::material_t());

	for (size_t i = 0; i < materials.size(); i++) {
		printf("material[%d].diffuse_texname = %s\n", int(i),
			materials[i].diffuse_texname.c_str());
	}


	//Load diffuse textures
	{
		for (size_t m = 0; m < materials.size(); m++)
		{
			tinyobj::material_t* mp = &materials[m];

			if (mp->diffuse_texname.length() > 0)
			{
				// Only load the texture if it is not already loaded
				if (res.textures.find(mp->diffuse_texname) == res.textures.end())
				{
					std::string texture_filename = base_dir +"/"+ mp->diffuse_texname;
					Texture2D* tmptex = new Texture2D(texture_filename.c_str());
					res.textures.insert(std::make_pair(mp->diffuse_texname, tmptex->GLtexture));
					delete tmptex;
				}
			}
		}
	}

	float bmin[3];
	float bmax[3];

	bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<float>::max();
	bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<float>::max();

	//load geomtry
	{

		for (size_t s = 0; s < shapes.size(); s++) {
			RenderElemnt o;
			std::vector<float> buffer;  // pos(3float), normal(3float), color(3float)

			// Check for smoothing group and compute smoothing normals
			std::map<int, glm::vec3> smoothVertexNormals;
			if (hasSmoothingGroup(shapes[s])) {
				std::cout << "Compute smoothingNormal for shape [" << s << "]" << std::endl;
				computeSmoothingNormals(attrib, shapes[s], smoothVertexNormals);
			}

			for (size_t f = 0; f < shapes[s].mesh.indices.size() / 3; f++) {
				tinyobj::index_t idx0 = shapes[s].mesh.indices[3 * f + 0];
				tinyobj::index_t idx1 = shapes[s].mesh.indices[3 * f + 1];
				tinyobj::index_t idx2 = shapes[s].mesh.indices[3 * f + 2];

				int current_material_id = shapes[s].mesh.material_ids[f];

				if ((current_material_id < 0) ||
					(current_material_id >= static_cast<int>(materials.size()))) {
					// Invaid material ID. Use default material.
					current_material_id = -1;// Default material is added to the last item in `materials`.
				}

				float diffuse[3];
				for (size_t i = 0; i < 3; i++) {
					diffuse[i] = materials[current_material_id].diffuse[i];
				}
				float tc[3][2];
				if (attrib.texcoords.size() > 0) {
					if ((idx0.texcoord_index < 0) || (idx1.texcoord_index < 0) ||
						(idx2.texcoord_index < 0)) {
						// face does not contain valid uv index.
						tc[0][0] = 0.0f;
						tc[0][1] = 0.0f;
						tc[1][0] = 0.0f;
						tc[1][1] = 0.0f;
						tc[2][0] = 0.0f;
						tc[2][1] = 0.0f;
					}
					else {
						assert(attrib.texcoords.size() >
							size_t(2 * idx0.texcoord_index + 1));
						assert(attrib.texcoords.size() >
							size_t(2 * idx1.texcoord_index + 1));
						assert(attrib.texcoords.size() >
							size_t(2 * idx2.texcoord_index + 1));

						// Flip Y coord.
						tc[0][0] = attrib.texcoords[2 * idx0.texcoord_index];
						tc[0][1] = 1.0f - attrib.texcoords[2 * idx0.texcoord_index + 1];
						tc[1][0] = attrib.texcoords[2 * idx1.texcoord_index];
						tc[1][1] = 1.0f - attrib.texcoords[2 * idx1.texcoord_index + 1];
						tc[2][0] = attrib.texcoords[2 * idx2.texcoord_index];
						tc[2][1] = 1.0f - attrib.texcoords[2 * idx2.texcoord_index + 1];
					}
				}
				else {
					tc[0][0] = 0.0f;
					tc[0][1] = 0.0f;
					tc[1][0] = 0.0f;
					tc[1][1] = 0.0f;
					tc[2][0] = 0.0f;
					tc[2][1] = 0.0f;
				}

				float v[3][3];
				for (int k = 0; k < 3; k++) {
					int f0 = idx0.vertex_index;
					int f1 = idx1.vertex_index;
					int f2 = idx2.vertex_index;
					assert(f0 >= 0);
					assert(f1 >= 0);
					assert(f2 >= 0);

					v[0][k] = attrib.vertices[3 * f0 + k];
					v[1][k] = attrib.vertices[3 * f1 + k];
					v[2][k] = attrib.vertices[3 * f2 + k];
					bmin[k] = glm::min(v[0][k], bmin[k]);
					bmin[k] = glm::min(v[1][k], bmin[k]);
					bmin[k] = glm::min(v[2][k], bmin[k]);
					bmax[k] = glm::max(v[0][k], bmax[k]);
					bmax[k] = glm::max(v[1][k], bmax[k]);
					bmax[k] = glm::max(v[2][k], bmax[k]);
				}

				float n[3][3];
				{
					bool invalid_normal_index = false;
					if (attrib.normals.size() > 0) {
						int nf0 = idx0.normal_index;
						int nf1 = idx1.normal_index;
						int nf2 = idx2.normal_index;

						if ((nf0 < 0) || (nf1 < 0) || (nf2 < 0)) {
							// normal index is missing from this face.
							invalid_normal_index = true;
						}
						else {
							for (int k = 0; k < 3; k++) {
								assert(size_t(3 * nf0 + k) < attrib.normals.size());
								assert(size_t(3 * nf1 + k) < attrib.normals.size());
								assert(size_t(3 * nf2 + k) < attrib.normals.size());
								n[0][k] = attrib.normals[3 * nf0 + k];
								n[1][k] = attrib.normals[3 * nf1 + k];
								n[2][k] = attrib.normals[3 * nf2 + k];
							}
						}
					}
					else {
						invalid_normal_index = true;
					}

					if (invalid_normal_index && !smoothVertexNormals.empty()) {
						// Use smoothing normals
						int f0 = idx0.vertex_index;
						int f1 = idx1.vertex_index;
						int f2 = idx2.vertex_index;

						if (f0 >= 0 && f1 >= 0 && f2 >= 0) {
							n[0][0] = smoothVertexNormals[f0][0];
							n[0][1] = smoothVertexNormals[f0][1];
							n[0][2] = smoothVertexNormals[f0][2];

							n[1][0] = smoothVertexNormals[f1][0];
							n[1][1] = smoothVertexNormals[f1][1];
							n[1][2] = smoothVertexNormals[f1][2];

							n[2][0] = smoothVertexNormals[f2][0];
							n[2][1] = smoothVertexNormals[f2][1];
							n[2][2] = smoothVertexNormals[f2][2];

							invalid_normal_index = false;
						}
					}

					if (invalid_normal_index) {
						// compute geometric normal
						CalcNormal(n[0], v[0], v[1], v[2]);
						n[1][0] = n[0][0];
						n[1][1] = n[0][1];
						n[1][2] = n[0][2];
						n[2][0] = n[0][0];
						n[2][1] = n[0][1];
						n[2][2] = n[0][2];
					}
				}

				for (int k = 0; k < 3; k++)
				{
					glm::vec3 vert = glm::vec3(v[k][0], v[k][1], v[k][2]);
						o.VNT.push_back(vert.x);
						o.VNT.push_back(vert.y);
						o.VNT.push_back(vert.z);

					//normalize vertices befor rendering.. to unit vectors..
					{
						glm::vec3 mn = glm::vec3(abs(bmin[0]), abs(bmin[1]), abs(bmin[2]));
						glm::vec3 mx = glm::vec3(bmax[0], bmax[1], bmax[2]);

						float max = glm::max(mn[0], mn[1]);
						max = glm::max(max, mn[2]);

						float max2 = glm::max(bmax[0], bmax[1]);
						max2 = glm::max(max, bmax[2]);

						float resmax = glm::max(max, max2);

						glm::vec3 bboxmin(-resmax);
						glm::vec3 bboxmax(+resmax);
						glm::vec3 scl = (vert / max + 1.0f) / 2.0f;


						//o.VNT.push_back(scl.x);
						//o.VNT.push_back(scl.y);
						//o.VNT.push_back(scl.z);
					}

					o.VNT.push_back(n[k][0]);
					o.VNT.push_back(n[k][1]);
					o.VNT.push_back(n[k][2]);
					//// Combine normal and diffuse to get color.
					float normal_factor = 0.2f;
					float diffuse_factor = 1 - normal_factor;
					float c[3] = { n[k][0] * normal_factor + diffuse[0] * diffuse_factor,
								  n[k][1] * normal_factor + diffuse[1] * diffuse_factor,
								  n[k][2] * normal_factor + diffuse[2] * diffuse_factor };
					float len2 = c[0] * c[0] + c[1] * c[1] + c[2] * c[2];
					if (len2 > 0.0f) {
						float len = sqrtf(len2);

						c[0] /= len;
						c[1] /= len;
						c[2] /= len;
					}
					o.VNT.push_back(c[0] * 0.5f + 0.5f);
					o.VNT.push_back(c[1] * 0.5f + 0.5f);
					o.VNT.push_back(c[2] * 0.5f + 0.5f);

					o.VNT.push_back(tc[k][0]);
					o.VNT.push_back(tc[k][1]);
				}
			}

			o.numTriangles = 0;

			// OpenGL viewer does not support texturing with per-face material.
			if (shapes[s].mesh.material_ids.size() > 0 &&
				shapes[s].mesh.material_ids.size() > s) {
				o.material_id = shapes[s].mesh.material_ids[0];  // use the material ID
																 // of the first face.
			}
			else {
				o.material_id = materials.size() - 1;  // = ID for default material.
			}
			printf("shape[%d] material_id %d\n", int(s), int(o.material_id));

		if ((o.material_id < materials.size()))
		{
			std::string diffuse_texname = materials[o.material_id].diffuse_texname;
			if (res.textures.find(diffuse_texname) != res.textures.end())
			{
				o.texture_id = res.textures[diffuse_texname];
			}
		}

			if (o.VNT.size() > 0)
			{
				o.numTriangles = (int)o.VNT.size() / (3 + 3 + 3 + 2) / 3;  // 3:vtx, 3:normal, 2:texcoord
				o.num_vertx = o.numTriangles * 3;
				printf("shape[%d] # of triangles = %d\n", static_cast<int>(s),
					o.numTriangles);
			}

			res.meshes.push_back(o);
		}

	}

	return res;
}

