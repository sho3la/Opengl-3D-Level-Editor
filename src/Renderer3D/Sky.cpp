#include "Sky.h"
#include "WidgetGL3D.h"

#include <glew.h>

Sky::Sky()
{
	Create();
}

Sky::~Sky()
{
}

void Sky::Create()
{

	const char* vs = R"CODE(
				#version 330

				layout (location = 0) in vec3 Position;


				out vec2 v;

				void main()
				{
					v = Position.xy;
					gl_Position = vec4(Position, 1.0);
				}
)CODE";

	const char* ps = R"CODE(
				#version 330

				uniform mat4 mat;
				uniform vec2 resolution;
				uniform vec3 lightPos;

				in vec2 v;

				out vec4 FragColor;

				vec3 skyColor( in vec3 rd )
				{
					vec3 sundir = normalize( lightPos );
    
					float yd = min(rd.y, 0.);
					rd.y = max(rd.y, 0.);
    
					vec3 col = vec3(0.);
    
					col += vec3(.9, .9 , .9) * exp(-rd.y*9.); // Red / Green 
					col += vec3(.3, .5, .7) * (1. - exp(-rd.y*8.) ) * exp(-rd.y*.9) ; // Blue
    
					col = mix(col*1.2, vec3(.8),  1.-exp(yd*100.)); // Fog
    
					col += vec3(1.0, .8, .55) * pow( max(dot(rd,sundir),0.), 15. ) * .3; // Sun
					col += vec3(1.0, .5, .3) * pow(max(dot(rd, sundir),0.), 300.0) ;
    
					return col;
				}
				void main()
				{
					vec3 dir = vec3( normalize( mat*vec4(v.xy*vec2(resolution.x/resolution.y,1),-1.5,0.0) ) );

					FragColor = vec4(skyColor(dir),1.);
				}
)CODE";

	Create_shader_program(_shader,vs,ps);


	float vertex[4][3];
	vertex[0][0] = -1.0f; vertex[1][0] = 1.0f; vertex[2][0] = -1.0f; vertex[3][0] = 1.0f;
	vertex[0][1] = -1.0f; vertex[1][1] = -1.0f; vertex[2][1] = 1.0f; vertex[3][1] = 1.0f;
	for (int i = 0; i < 4; i++)
		vertex[i][2] = 0.f;

	glGenVertexArrays(1, &vao_id);
	glGenBuffers(1, &vbo_id);

	glBindVertexArray(vao_id);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, 4*3*sizeof(float), vertex, GL_STATIC_DRAW);

	// position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void Sky::Draw()
{
	glBindVertexArray(vao_id);
	use_shaderprogram(_shader);
	setMat4(_shader,"mat",glm::inverse(WidgetGL3D::cam.view));
	setVec2(_shader,"resolution",WidgetGL3D::cam.aspect_Ratio);
	setVec3(_shader,"lightPos",glm::vec3(50));

	glDisable(GL_DEPTH_TEST);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glEnable(GL_DEPTH_TEST);
	glBindVertexArray(0);
}
