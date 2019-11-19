#include "Material/Shader.h"



#include <glew.h>

inline static void checkCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

void Create_shader_program(Shader& self, const char* vertexPath, const char* fragmentPath)
{
	const char* vShaderCode = vertexPath;
	const char * fShaderCode = fragmentPath;
	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// shader Program
	self.ID = glCreateProgram();
	glAttachShader(self.ID, vertex);
	glAttachShader(self.ID, fragment);
	glLinkProgram(self.ID);
	checkCompileErrors(self.ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void use_shaderprogram(Shader & self)
{
	glUseProgram(self.ID);
}

void setBool(Shader & self, const std::string & name, bool value)
{
	glUniform1i(glGetUniformLocation(self.ID, name.c_str()), (int)value);
}

void setInt(Shader & self, const std::string & name, int value)
{
	glUniform1i(glGetUniformLocation(self.ID, name.c_str()), value);
}

void setFloat(Shader & self, const std::string & name, float value)
{
	glUniform1f(glGetUniformLocation(self.ID, name.c_str()), value);
}

void setVec2(Shader & self, const std::string & name, const glm::vec2 & value)
{
	glUniform2fv(glGetUniformLocation(self.ID, name.c_str()), 1, &value[0]);
}

void setVec2(Shader & self, const std::string & name, float x, float y)
{
	glUniform2f(glGetUniformLocation(self.ID, name.c_str()), x, y);
}

void setVec3(Shader & self, const std::string & name, const glm::vec3 & value)
{
	glUniform3fv(glGetUniformLocation(self.ID, name.c_str()), 1, &value[0]);
}

void setVec3(Shader & self, const std::string & name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(self.ID, name.c_str()), x, y, z);
}

void setVec4(Shader & self, const std::string & name, const glm::vec4 & value)
{
	glUniform4fv(glGetUniformLocation(self.ID, name.c_str()), 1, &value[0]);
}

void setVec4(Shader & self, const std::string & name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(self.ID, name.c_str()), x, y, z, w);
}

void setMat2(Shader & self, const std::string & name, const glm::mat2 & mat)
{
	glUniformMatrix2fv(glGetUniformLocation(self.ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void setMat3(Shader & self, const std::string & name, const glm::mat3 & mat)
{
	glUniformMatrix3fv(glGetUniformLocation(self.ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void setMat4(Shader & self, const std::string & name, const glm::mat4 &mat)
{
	glUniformMatrix4fv(glGetUniformLocation(self.ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
