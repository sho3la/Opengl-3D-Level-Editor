#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Default camera values
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
const float YAW = -90.0f;
const float PITCH = 0.0f;

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

struct EditorCamera
{
	// Camera Attributes
	static glm::vec3 Position;
	static glm::vec2 aspect_Ratio;

	static glm::mat4 projection;
	static glm::mat4 view;

	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// Euler Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
};

void CreateEditorCamera(EditorCamera& self,
						glm::vec3 position,
						glm::vec3 up_vector,
						glm::vec2 aspecRatio,
						float yaw,
						float pitch);

glm::mat4 CreateViewMatrix(EditorCamera& self);

glm::mat4 CreateProjectionMatrix(EditorCamera& self);

void CameraKeyboard_input(EditorCamera& self,
						Camera_Movement direction,
						float deltaTime);

void CameraMouse_input(EditorCamera& self, 
						float xoffset, 
						float yoffset, 
						bool constrainPitch = true);


void CameraMouse_WheelScroll(EditorCamera& self,float yoffset);

void CameraMouse_Pan(EditorCamera& self, float xoffset, float yoffset);