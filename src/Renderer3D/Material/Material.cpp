#include "Material/Material.h"
#include "WidgetGL3D.h"

#include <glew.h>

Material::Material()
{
	const char* vs = R"CODE(
				#version 330 core
				layout (location = 0) in vec3 aPos;
				layout (location = 1) in vec3 aNormal;
				layout (location = 2) in vec2 aTexCoords;


				out vec2 TexCoords;
				out vec3 WorldPos;
				out vec3 Normal;
				out vec2 uv;

				uniform mat4 ViewProjection;
				uniform mat4 model;

				void main()
				{
					TexCoords = aTexCoords;
					WorldPos = vec3(model * vec4(aPos, 1.0));
					Normal = mat3(model) * aNormal;   
					uv = aPos.xy*vec2(.5) + vec2(.5);

					gl_Position =  ViewProjection * vec4(WorldPos, 1.0);

				}
)CODE";

	const char* fs = R"CODE(
				#version 330 core
				out vec4 FragColor;
				in vec2 TexCoords;
				in vec3 WorldPos;
				in vec3 Normal;
				in vec2 uv;

				uniform sampler2D _texture;

				uniform vec3 lightPos;
				uniform vec3 viewPos;



				vec3 Uncharted2ToneMapping(vec3 color)
				{
						float A = 0.15;
						float B = 0.50;
						float C = 0.10;
						float D = 0.20;
						float E = 0.02;
						float F = 0.30;
						float W = 11.2;
						float exposure = 2.;
						color *= exposure;
						color = ((color * (A * color + C * B) + D * E) / (color * (A * color + B) + D * F)) - E / F;
						float white = ((W * (A * W + C * B) + D * E) / (W * (A * W + B) + D * F)) - E / F;
						color /= white;
						return color;
				}

				void main()
				{

					vec4 sample = texture(_texture, TexCoords);
					vec3 col = sample.rgb;
					vec3 normal = normalize(Normal);
					vec3 diff = vec3(1.) * max(dot(normal,normalize(lightPos-WorldPos)), 0.);
					float shad = 1.;

					vec3 indirect = vec3(0.5,0.5,0.5);

					col = col*(diff*shad+indirect*.5);

					col = Uncharted2ToneMapping(col * 5);

					FragColor = vec4(col, sample.a);
				}
)CODE";


	Create_shader_program(program, vs, fs);

	Set_Textures("Resources\\Textures\\checkboard.png");
}

Material::~Material()
{
	if(Texture != nullptr) delete Texture;
}

void Material::Set_Textures(const char * albedo)
{
	//internal image as initialization..
	Texture = new Texture2D(albedo);
	use_shaderprogram(program);
	setInt(program, "texture", 0);
}


void Material::Use_Material(glm::mat4 VP_Matrx, glm::mat4 Model_Matrx)
{
	use_shaderprogram(program);
	setMat4(program,"ViewProjection",VP_Matrx);
	setMat4(program,"model",Model_Matrx);

	//light probs
	setVec3(program,"lightPos",glm::vec3(50.0f));
	setVec3(program,"viewPos",WidgetGL3D::cam.Position);
}
