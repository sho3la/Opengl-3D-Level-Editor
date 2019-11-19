#pragma once
#include <QSet>
#include "EditorCamera.h"
#include "Geomtry\Shape.h"
#include "Scene.h"

struct EditorInput
{
	//keyboard
	QSet<int> keysPressed;
	QSet<Shape_Type> ui_cmd;
	bool m_bFirstRelease = false;

	//mouse
	static bool Rightmousepress;
	static bool Midlemousepress;
	static bool Leftmousepress ;
	float lastX = 0.0f;
	float lastY = 0.0f;
	bool firstMouse = true;

	static glm::vec2 MousePosition;
	static glm::vec2 DeltaMovment;
};

void push_event(EditorInput& self, int key);

void pop_event(EditorInput& self, int key);

void ProcessKeys(EditorCamera& cam, int k);

void ProcessUi_input(EditorInput& self, Scene* scene);

void Update_input_Keys(EditorInput& self, EditorCamera & cam);