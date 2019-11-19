#include "Viewer.h"
#include "States.h"

#include <QToolBar>
#include <QGridLayout>
#include <QFileDialog>

Viewer::Viewer(QWidget *parent) : QMainWindow(parent)
{
	//set default state as maxmized window..
	this->setWindowState(Qt::WindowMaximized);
	QWidget* central = new QWidget();
	setCentralWidget(central);
	

	Create_VToolbar();
	Create_HToolbar();

	//create all widgets to add...
	Scene_Editor = new WidgetGL3D();
	int x = Scene_Editor->geometry().width();
	int y = Scene_Editor->geometry().height();
	Transform_Controll = new QWidget();
	Transform_Controll->setMaximumWidth(250);
	

	QGridLayout* layout = new QGridLayout(this);
	layout->addWidget(Scene_Editor, 0, 0);
	layout->addWidget(Transform_Controll, 0, 1);
	central->setLayout(layout);
}

void Viewer::Create_VToolbar()
{
	//vertical toolbar
	QPixmap cubepix("Resources/cube_blue.png");
	QPixmap spherepix("Resources/bullet_ball_blue.png");
	QPixmap conepix("Resources/object_cone.png");
	QPixmap cylinderpix("Resources/cylinder_ico.png");
	QPixmap Planepix("Resources/plane_ico.png");
	QPixmap avatarpix("Resources/user_generic2.png");
	QPixmap camerapix("Resources/movie_camera.png");

	QToolBar *V_toolbar = new QToolBar();
	addToolBar(Qt::LeftToolBarArea, V_toolbar);
	V_toolbar->setMovable(false);

	//add actions..
	QAction *cube = V_toolbar->addAction(QIcon(cubepix), "New Cube");
	QAction *sphere = V_toolbar->addAction(QIcon(spherepix), "New Sphere");
	QAction * cylinder = V_toolbar->addAction(QIcon(cylinderpix), "New Cylinder");
	QAction * cone = V_toolbar->addAction(QIcon(conepix), "New Cone");
	QAction * Plane = V_toolbar->addAction(QIcon(Planepix), "New Plane");
	V_toolbar->addSeparator();
	QAction * avatar = V_toolbar->addAction(QIcon(avatarpix), "New Avatar");
	V_toolbar->addSeparator();
	QAction * camera = V_toolbar->addAction(QIcon(camerapix), "New Camera");

	connect(cube, &QAction::triggered, this, &Viewer::New_Cube);
	connect(sphere, &QAction::triggered, this, &Viewer::New_Sphere);
	connect(cylinder, &QAction::triggered, this, &Viewer::New_Cylinder);
	connect(cone, &QAction::triggered, this, &Viewer::New_Cone);
	connect(Plane, &QAction::triggered, this, &Viewer::New_Plane);
	connect(avatar, &QAction::triggered, this, &Viewer::New_Avatar);
	connect(camera, &QAction::triggered, this, &Viewer::New_Camera);
}

void Viewer::Create_HToolbar()
{
	//horizontal toolbar
	QToolBar *H_toolbar = addToolBar("horizontal");
	H_toolbar->setMovable(false);

	//add actions..
	H_toolbar->addAction(QIcon("Resources/new_ico.png"), "New Scene");
	H_toolbar->addAction(QIcon("Resources/openfolder_ico.png"), "Open Folder");
	H_toolbar->addAction(QIcon("Resources/save_ico.png"), "Save");
	H_toolbar->addSeparator();
	QAction *trans_action = H_toolbar->addAction(QIcon("Resources/trans_ico.png"), "Translation");
	QAction *rot_action = H_toolbar->addAction(QIcon("Resources/rot_ico.png"), "Rotation");
	QAction *scal_action = H_toolbar->addAction(QIcon("Resources/scal_ico.png"), "Scale");

	connect(trans_action, &QAction::triggered, this, &Viewer::Active_Translation);
	connect(rot_action, &QAction::triggered, this, &Viewer::Active_Rotation);
	connect(scal_action, &QAction::triggered, this, &Viewer::Active_Scale);
}

void Viewer::Active_Rotation()
{
	//States::AC_Transform = AC_Rotation;
}

void Viewer::Active_Scale()
{
	States::AC_Transform = AC_Scale;
}

void Viewer::New_Cube()
{
	Scene_Editor->input.ui_cmd += CUBE;
}

void Viewer::New_Sphere()
{
	Scene_Editor->input.ui_cmd += SPHERE;
}

void Viewer::New_Cylinder()
{
}

void Viewer::New_Cone()
{
}

void Viewer::New_Plane()
{
	Scene_Editor->input.ui_cmd += PLANE;
}

void Viewer::New_Avatar()
{
	//open file dialog and get path of this model
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Model File"), "", tr(""));

	filenamepath = fileName.toLocal8Bit();
	char* fiel = filenamepath.data();
	States::CurrentModelFilePath = fiel;

	//push in command stack to generate this model
	Scene_Editor->input.ui_cmd += MODELOBJ;
}

void Viewer::New_Camera()
{
}

void Viewer::Active_Translation()
{
	States::AC_Transform = AC_Translation;
}
