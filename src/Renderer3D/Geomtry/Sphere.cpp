#include "Geomtry/Sphere.h"
#include "Geomtry/GeomtryGeneration.h"

#include <glew.h>

Sphere::~Sphere()
{
	material = nullptr;
}

void Sphere::Create()
{
	RenderElemnt el =  GeoGenerator::Sphere();
	VertNormTex = el.VNT;
	indices = el.indices;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertNormTex[0]) * VertNormTex.size(), &VertNormTex[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);


	//normals attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));


	// texturecorrd attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
}

void Sphere::Draw(glm::mat4 VP_Matrx)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

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

	glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, 0);
}

void Sphere::Set_Texture(const char * albedo)
{
	if (Texture != nullptr) delete Texture;

	Texture = new Texture2D(albedo);
}
