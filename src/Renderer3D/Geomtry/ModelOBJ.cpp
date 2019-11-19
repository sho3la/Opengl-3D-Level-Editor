#include "Geomtry/ModelOBJ.h"
#include "Geomtry/GeomtryGeneration.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <glew.h>

ModelOBJ::~ModelOBJ()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (Texture != nullptr) delete Texture;
}


void ModelOBJ::Create(const char* filename)
{

	ModelRenderObject modelobj = GeoGenerator::Model3D(filename);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	for (auto submesh : modelobj.meshes)
	{
		meshes obj;
		obj.VertNormTex = submesh.VNT;
		obj.texture_id = submesh.texture_id;
		obj.num_vertx = submesh.num_vertx;
		

		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(obj.VertNormTex[0]) * obj.VertNormTex.size(), &obj.VertNormTex[0], GL_STATIC_DRAW);

		obj.vbo_id = VBO;
		submeshes.push_back(obj);
	}
}


void draw_PivotBox_Debug() {

	// Cube 1x1x1, centered on origin
	GLfloat vertices[] = {
	  -0.5, -0.5, -0.5, 1.0,
	   0.5, -0.5, -0.5, 1.0,
	   0.5,  0.5, -0.5, 1.0,
	  -0.5,  0.5, -0.5, 1.0,
	  -0.5, -0.5,  0.5, 1.0,
	   0.5, -0.5,  0.5, 1.0,
	   0.5,  0.5,  0.5, 1.0,
	  -0.5,  0.5,  0.5, 1.0,
	};

	GLuint vbo_vertices;
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLushort elements[] = {
	  0, 1, 2, 3,
	  4, 5, 6, 7,
	  0, 4, 1, 5, 2, 6, 3, 7
	};
	GLuint ibo_elements;
	glGenBuffers(1, &ibo_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,  // attribute
		4,                  // number of elements per vertex, here (x,y,z,w)
		GL_FLOAT,           // the type of each element
		GL_FALSE,           // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, 0);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, (GLvoid*)(4 * sizeof(GLushort)));
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, (GLvoid*)(8 * sizeof(GLushort)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo_vertices);
	glDeleteBuffers(1, &ibo_elements);
}

void ModelOBJ::Draw(glm::mat4 VP_Matrx)
{
	glBindVertexArray(VAO);

	transform.Model_Matrx = glm::mat4(1.0f);
	transform.Model_Matrx = glm::translate(transform.Model_Matrx, transform.position);

	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_z), glm::vec3(0.0f, 0.0f, 1.0f));

	transform.Model_Matrx = glm::scale(transform.Model_Matrx, transform.scale);


	for(auto mesh : submeshes)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo_id);
		// position attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
		//normals attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
		// texturecorrd attribute
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));

		if (mesh.texture_id > 0)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh.texture_id);
			material->Use_Material(VP_Matrx, transform.Model_Matrx);
		}
		else
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, material->Texture->GLtexture);
			material->Use_Material(VP_Matrx, transform.Model_Matrx);
		}



		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mesh.num_vertx);

		draw_PivotBox_Debug();
	}
}

void ModelOBJ::Set_Texture(const char * albedo)
{
	if (Texture != nullptr) delete Texture;

	Texture = new Texture2D(albedo);
}
