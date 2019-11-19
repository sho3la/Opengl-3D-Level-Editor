#include "Input.h"
#include "States.h"

//#include <stdio.h>      /* printf, NULL */
//#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */


glm::vec2 EditorInput::MousePosition = glm::vec2(0);
glm::vec2 EditorInput::DeltaMovment = glm::vec2(0);

bool EditorInput::Rightmousepress = false;
bool EditorInput::Midlemousepress = false;
bool EditorInput::Leftmousepress = false;

void push_event(EditorInput& self, int key)
{
	self.m_bFirstRelease = true;
	self.keysPressed += key;
}

void pop_event(EditorInput& self, int key)
{
	self.m_bFirstRelease = false;
	self.keysPressed -= key;
}

void ProcessKeys(EditorCamera & cam, int k)
{
	switch (k)
	{
	case Qt::Key_Down:
		CameraKeyboard_input(cam, Camera_Movement::BACKWARD, 0.1f);
		break;
	case Qt::Key_Up:
		CameraKeyboard_input(cam, Camera_Movement::FORWARD, 0.1f);
		break;
	case Qt::Key_Left:
		CameraKeyboard_input(cam, Camera_Movement::LEFT, 0.1f);
		break;
	case Qt::Key_Right:
		CameraKeyboard_input(cam, Camera_Movement::RIGHT, 0.1f);
		break;
	default:
		break;
	}


}

void ProcessUi_input(EditorInput& self, Scene* scene)
{
	for (auto c : self.ui_cmd)
	{
		switch (c)
		{
		case SPHERE:
			scene->Add_Object(SPHERE);
			break;

		case CUBE:
			scene->Add_Object(CUBE);
			break;

		case PLANE:
			scene->Add_Object(PLANE);
			break;
		case MODELOBJ:
			scene->Add_Object(MODELOBJ,States::CurrentModelFilePath);
			States::CurrentModelFilePath = nullptr;
			break;
		default:
			break;
		}
	}

	self.ui_cmd.clear();
}

void Update_input_Keys(EditorInput& self, EditorCamera & cam)
{
	for each (auto var in self.keysPressed)
	{
		ProcessKeys(cam, var);
	}
}
