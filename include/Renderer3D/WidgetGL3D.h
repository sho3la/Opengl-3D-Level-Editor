#pragma once
#include <glew.h>
#include <QOpenGLWidget>

#include "Renderer3D/EditorCamera.h"
#include "Renderer3D/Input.h"
#include "Renderer3D/Scene.h"
#include "Renderer3D/Sky.h"
#include "Renderer3D/SceneNavigation.h"

class WidgetGL3D : public QOpenGLWidget
{
	Q_OBJECT

public:
	WidgetGL3D(QWidget *parent = nullptr);

	~WidgetGL3D();

	EditorInput input;
	static EditorCamera cam;

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;

	//mouse events
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event);

	//keyboard events
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
private:
	glm::mat4 vp;
	Scene* scene;
	Shape* grid;
	Sky* sky;
	SceneNavigator* _scnnav;
};