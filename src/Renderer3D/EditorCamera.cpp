#include "EditorCamera.h"


glm::vec3 EditorCamera::Position = glm::vec3(0);
glm::vec2 EditorCamera::aspect_Ratio = glm::vec3(0);

glm::mat4 EditorCamera::projection = glm::mat4(1);
glm::mat4 EditorCamera::view = glm::mat4(1);

inline static void updateCameraVectors(EditorCamera& self)
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(self.Yaw)) * cos(glm::radians(self.Pitch));
	front.y = sin(glm::radians(self.Pitch));
	front.z = sin(glm::radians(self.Yaw)) * cos(glm::radians(self.Pitch));
	self.Front = glm::normalize(front);

	// Also re-calculate the Right and Up vector
	self.Right = glm::normalize(glm::cross(self.Front, self.WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	self.Up = glm::normalize(glm::cross(self.Right, self.Front));
}

void CreateEditorCamera(EditorCamera& self, glm::vec3 position , glm::vec3 up_vector,glm::vec2 aspecRatio , float yaw, float pitch)
{
	self.Front = glm::vec3(0.0f, 0.0f, -1.0f);
	self.MovementSpeed = SPEED;
	self.MouseSensitivity = SENSITIVITY;
	self.Zoom = ZOOM;

	self.aspect_Ratio = aspecRatio;

	self.Position = position;
	self.WorldUp = up_vector;
	self.Yaw = yaw;
	self.Pitch = pitch;
	updateCameraVectors(self);
}

glm::mat4 CreateViewMatrix(EditorCamera& self)
{
	return glm::lookAt(self.Position, self.Position + self.Front, self.Up);
}

glm::mat4 CreateProjectionMatrix(EditorCamera & self)
{
	return glm::perspective(glm::radians(self.Zoom), self.aspect_Ratio.x / self.aspect_Ratio.y, 0.1f, 1000.0f);
}

void CameraKeyboard_input(EditorCamera& self,Camera_Movement direction, float deltaTime)
{
	float velocity = self.MovementSpeed * deltaTime;
	if (direction == FORWARD)
		self.Position += self.Front * velocity;
	if (direction == BACKWARD)
		self.Position -= self.Front * velocity;
	if (direction == LEFT)
		self.Position -= self.Right * velocity;
	if (direction == RIGHT)
		self.Position += self.Right * velocity;
}

void CameraMouse_input(EditorCamera & self, float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= self.MouseSensitivity;
	yoffset *= self.MouseSensitivity;

	self.Yaw += xoffset;
	self.Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (self.Pitch > 89.0f)
			self.Pitch = 89.0f;
		if (self.Pitch < -89.0f)
			self.Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors(self);
}

void CameraMouse_WheelScroll(EditorCamera & self, float yoffset)
{
	if (self.Zoom >= 1.0f && self.Zoom <= 45.0f)
		self.Zoom -= yoffset;
	if (self.Zoom <= 1.0f)
		self.Zoom = 1.0f;
	if (self.Zoom >= 45.0f)
		self.Zoom = 45.0f;
}

void CameraMouse_Pan(EditorCamera & self, float xoffset, float yoffset)
{
	float velocity = self.MovementSpeed * 0.01f/*deltatime*/;
	self.Position.y += -yoffset * velocity;
	//self.Position.x += xoffset * velocity;
}
