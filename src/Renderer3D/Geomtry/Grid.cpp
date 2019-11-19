#include "Geomtry/Grid.h"
#include "Geomtry/GeomtryGeneration.h"

#include <glew.h>

Grid::Grid(Material* shading)
{
	m_gridsize = glm::ivec2(20,20);
	material = shading;
	Create();
}

Grid::~Grid()
{
	material = nullptr;
}

void Grid::Create()
{
	RenderElemnt el = GeoGenerator::Grid(m_gridsize.x,m_gridsize.y);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0, (void*)0);
}

void Grid::Draw(glm::mat4 VP_Matrx)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	transform.Model_Matrx = glm::mat4(1.0f);
	transform.Model_Matrx = glm::translate(transform.Model_Matrx, transform.position);

	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform.Model_Matrx = glm::rotate(transform.Model_Matrx, glm::radians(transform.rotation_z), glm::vec3(0.0f, 0.0f, 1.0f));

	transform.Model_Matrx = glm::scale(transform.Model_Matrx, transform.scale);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material->Texture->GLtexture);
		material->Use_Material(VP_Matrx, transform.Model_Matrx);

	glDrawElements(GL_LINES, m_gridsize.x * m_gridsize.y, GL_UNSIGNED_INT, 0);
}
