#pragma once

#include <QtWidgets/QMainWindow>
#include "Renderer3D/WidgetGL3D.h"

class Viewer : public QMainWindow
{
	Q_OBJECT

public:
	Viewer(QWidget *parent = Q_NULLPTR);

	void Create_VToolbar();
	void Create_HToolbar();


private slots:
	void Active_Translation();
	void Active_Rotation();
	void Active_Scale();

	void New_Cube();
	void New_Sphere();
	void New_Cylinder();
	void New_Cone();
	void New_Plane();
	void New_Avatar();
	void New_Camera();

private:
	WidgetGL3D* Scene_Editor;
	QWidget* Transform_Controll;
	QByteArray filenamepath;
};
