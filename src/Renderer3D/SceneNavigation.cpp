#include "SceneNavigation.h"
#include "Material/Texture2D.h"
#include "EditorCamera.h"
#include "WidgetGL3D.h"

#include <glew.h>

// settings


void Create_New_SceneNavigator(SceneNavigator & self,glm::vec2 aspecRatio)
{
	// configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

	// build and compile shaders
    // -------------------------
			const char* vs_code = R"CODE(
			#version 330 core
			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec2 aTexCoords;

			out vec2 TexCoords;

			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;

			void main()
			{
				TexCoords = aTexCoords;    
				gl_Position = projection * view * model * vec4(aPos, 1.0);
			}
)CODE";

	const char* ps_code = R"CODE(
			#version 330 core
			out vec4 FragColor;

			in vec2 TexCoords;

			uniform sampler2D texture1;

			void main()
			{
				FragColor = texture(texture1, TexCoords);
			}
)CODE";

	Create_shader_program(self.shader_program,vs_code, ps_code);

		vs_code = R"CODE(
			#version 330 core
			layout (location = 0) in vec2 aPos;
			layout (location = 1) in vec2 aTexCoords;

			out vec2 TexCoords;

			uniform mat4 model;
			uniform mat4 projection;

			void main()
			{
				TexCoords = aTexCoords;
				gl_Position = projection * model * vec4(aPos.x, aPos.y, 0.0, 1.0); 
			}
)CODE";

		ps_code = R"CODE(
			#version 330 core
			out vec4 FragColor;

			in vec2 TexCoords;

			uniform sampler2D screenTexture;

			void main()
			{
				vec4 texColor = texture(screenTexture, TexCoords);
				if(texColor.r < 0.1)
					discard;
				FragColor = texColor;
			} 
)CODE";

	Create_shader_program(self.screenshader_program,vs_code, ps_code);


	// set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
	// cube VAO

	float cubeVertices[180] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};;

    float quadVertices[24] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    glGenVertexArrays(1, &self.cubeVAO);
    glGenBuffers(1, &self.cubeVBO);
    glBindVertexArray(self.cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, self.cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	Texture2D* tex = new Texture2D("SceneNAV.png");
	self.Qubetexture = tex->GLtexture;
	delete tex;

	use_shaderprogram(self.shader_program);
	setInt(self.shader_program, "texture1", 0);

    // screen quad VAO
    
    glGenVertexArrays(1, &self.quadVAO);
    glGenBuffers(1, &self.quadVBO);
    glBindVertexArray(self.quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, self.quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	use_shaderprogram(self.screenshader_program);
	setInt(self.screenshader_program,"screenTexture", 0);

	self.QuadPosition = glm::vec2(self.SCR_WIDTH,self.SCR_HEIGHT);

	// framebuffer configuration
    // -------------------------

    glGenFramebuffers(1, &self.framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, self.framebuffer);
    // create a color attachment texture
    
    glGenTextures(1, &self.textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, self.textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, self.SCR_WIDTH,self.SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, self.textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    
    glGenRenderbuffers(1, &self.rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, self.rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, self.SCR_WIDTH, self.SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, self.rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete! \n");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_BLEND);
}


void Draw_SceneNavigator(SceneNavigator & self)
{
	// render
	// ------
	// bind to framebuffer and draw scene as we normally would to color texture 
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &self.CurrentFBO_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, self.framebuffer);
	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

	// make sure we clear the framebuffer's content
	glClearColor(0.1f, 0.1f, 0.1f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	use_shaderprogram(self.shader_program);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0,0,2), glm::vec3(0,0,-1), glm::vec3(0,1,0));
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)self.QuadSize.x / self.QuadSize.y, 0.1f, 1000.0f);
	setMat4(self.shader_program, "projection", projection);
	setMat4(self.shader_program, "view", view);

	// cube
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, self.Qubetexture);
	glBindVertexArray(self.cubeVAO);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(WidgetGL3D::cam.Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(WidgetGL3D::cam.Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	setMat4(self.shader_program, "model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	glBindFramebuffer(GL_FRAMEBUFFER, self.CurrentFBO_ID);

	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.

	use_shaderprogram(self.screenshader_program);
	glBindVertexArray(self.quadVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, self.textureColorbuffer);	// use the color attachment texture as the texture of the quad plane

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(self.QuadSize.x,self.QuadSize.y,0.0f));
	model = glm::scale(model, glm::vec3(self.QuadSize, 1.0f));

	setMat4(self.screenshader_program, "model", model);
	projection = glm::ortho(0.0f, (float)self.SCR_WIDTH,(float)self.SCR_HEIGHT, 0.0f, -1.0f, 1.0f);
	setMat4(self.screenshader_program, "projection", projection);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.49f,0.49f,0.49f,1.0f);
}
