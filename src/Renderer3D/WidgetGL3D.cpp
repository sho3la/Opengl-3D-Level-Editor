#include "WidgetGL3D.h"
#include "Geomtry/Grid.h"
#include "Selection.h"
#include "Manipulator/Manipulater.h"

#include <QKeyEvent>

EditorCamera WidgetGL3D::cam = EditorCamera{};

WidgetGL3D::WidgetGL3D(QWidget *parent) : QOpenGLWidget(parent)
{
	setFocusPolicy(Qt::FocusPolicy::StrongFocus);
}

WidgetGL3D::~WidgetGL3D()
{
	delete scene;
	delete grid;
	delete sky;
	delete _scnnav;
}

void WidgetGL3D::initializeGL()
{
	if (glewInit() != GLEW_OK)
	{
		printf("erorr loading opengl check your driver..");
	}



	CreateEditorCamera(cam, glm::vec3(0.0f, 3.0f, 10.0f),
						glm::vec3(0.0f, 1.0f, 0.0f),
						glm::vec2(this->geometry().width(),this->geometry().height()),
						YAW, PITCH);

	scene = new Scene();

	//after creating scene use unified material to all...
	grid = new Grid(scene->_material);

	//create sky for better experience.
	sky = new Sky();
	_scnnav = new SceneNavigator;
	Create_New_SceneNavigator(*_scnnav,cam.aspect_Ratio);
}


void WidgetGL3D::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5,0.5,0.5,1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	EditorCamera::projection = CreateProjectionMatrix(cam);
	EditorCamera::view = CreateViewMatrix(cam);
	vp = EditorCamera::projection  * EditorCamera::view;

	//editor features..
	sky->Draw();
	Draw_SceneNavigator(*_scnnav);
	grid->Draw(vp);

	//scene render
	scene->Draw(vp);
	
	//update input
	EditorInput::MousePosition.x = mapFromGlobal(QCursor::pos()).x();
	EditorInput::MousePosition.y = mapFromGlobal(QCursor::pos()).y();
	Update_input_Keys(input,cam);
	ProcessUi_input(input, scene);
	update();
}

void WidgetGL3D::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	cam.aspect_Ratio = glm::vec2( width, height);
}

void WidgetGL3D::mousePressEvent(QMouseEvent * event)
{
	setFocusPolicy(Qt::FocusPolicy::StrongFocus);
	if (event->button() == Qt::RightButton)
	{
		EditorInput::Rightmousepress = true;
		input.lastX = EditorInput::MousePosition.x;
		input.lastY = EditorInput::MousePosition.y;
	}
	else if (event->button() == Qt::MiddleButton)
	{
		EditorInput::Midlemousepress = true;
		input.lastX = EditorInput::MousePosition.x;
		input.lastY = EditorInput::MousePosition.y;
	}
	else if (event->button() == Qt::LeftButton)
	{
		EditorInput::Leftmousepress = true;
		input.lastX = EditorInput::MousePosition.x;
		input.lastY = EditorInput::MousePosition.y;

		scene->Active_Gizmo()->Active_Axis();

		if(scene->Active_Gizmo()->state == NO_AXIS)
			scene->Select_Object();
	}

}

void WidgetGL3D::mouseReleaseEvent(QMouseEvent * event)
{
	EditorInput::Rightmousepress = false;
	EditorInput::Midlemousepress = false;
	EditorInput::Leftmousepress = false;

	EditorInput::DeltaMovment.x = 0;
	EditorInput::DeltaMovment.y = 0;

	scene->Active_Gizmo()->Reset_State();
}

void WidgetGL3D::mouseMoveEvent(QMouseEvent * event)
{
	if (EditorInput::Rightmousepress)
	{
		if (input.firstMouse)
		{
			input.lastX = event->pos().x();
			input.lastY = event->pos().y();
			input.firstMouse = false;
		}

		EditorInput::DeltaMovment.x = event->pos().x() - input.lastX;
		EditorInput::DeltaMovment.y = input.lastY - event->pos().y(); // reversed since y-coordinates go from bottom to top

		input.lastX = event->pos().x();
		input.lastY = event->pos().y();

		CameraMouse_input(cam, EditorInput::DeltaMovment.x, EditorInput::DeltaMovment.y);
	}
	else if (EditorInput::Midlemousepress)
	{
		//EditorInput::DeltaMovment.x = input.lastY - event->pos().x();
		EditorInput::DeltaMovment.y = input.lastY - event->pos().y();
		input.lastY = event->pos().y();
		input.lastX = event->pos().x();
		CameraMouse_Pan(cam,EditorInput::DeltaMovment.x,EditorInput::DeltaMovment.y);
	}
	else if (EditorInput::Leftmousepress)
	{
		if (scene->selectedObj_indx != -1)
		{
			glm::vec3 pos = glm::vec3(event->pos().x(), event->pos().y(), 1);
			glm::vec3 dragdir = pos - glm::vec3(input.lastX, input.lastY, 1);

			scene->Active_Gizmo()->Move(scene->elemnts[scene->selectedObj_indx], dragdir);
			input.lastY = event->pos().y();
			input.lastX = event->pos().x();
		}
	}
}

void WidgetGL3D::wheelEvent(QWheelEvent * event)
{
	QPoint numDegrees = event->angleDelta() / 8;
	CameraMouse_WheelScroll(cam, numDegrees.y() / 10);
}

void WidgetGL3D::keyPressEvent(QKeyEvent * event)
{
	push_event(input,event->key());
}

void WidgetGL3D::keyReleaseEvent(QKeyEvent * event)
{
	pop_event(input, event->key());
}

