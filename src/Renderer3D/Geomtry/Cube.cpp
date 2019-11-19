#include "Geomtry/Cube.h"
#include "Geomtry/GeomtryGeneration.h"

#include <glew.h>

Cube::~Cube()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (Texture != nullptr) delete Texture;
}

void Cube::Create()
{
	RenderElemnt el = GeoGenerator::Cube();
	VertNormTex = el.VNT;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertNormTex[0]) * VertNormTex.size(), &VertNormTex[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texturecorrd attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Cube::Draw(glm::mat4 VP_Matrx)
{
	glBindVertexArray(VAO);

	transform.Model_Matrx = glm::mat4(1.0f);
	transform.Model_Matrx = glm::translate(transform.Model_Matrx, transform.position);

	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_z), glm::vec3(0.0f, 0.0f, 1.0f));

	transform.Model_Matrx = glm::scale(transform.Model_Matrx, transform.scale);

	if (Texture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture->GLtexture);
		material->Use_Material(VP_Matrx, transform.Model_Matrx);
	}
	else
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material->Texture->GLtexture);
		material->Use_Material(VP_Matrx, transform.Model_Matrx);
	}
		

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::Set_Texture(const char * albedo)
{
	if (Texture != nullptr) delete Texture;

	Texture = new Texture2D(albedo);
}
