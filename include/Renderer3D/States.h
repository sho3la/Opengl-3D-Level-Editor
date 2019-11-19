#pragma once

enum Active_Transfromation
{
	AC_Translation,
	AC_Rotation,
	AC_Scale,
	None
};

class States
{
public:
	static Active_Transfromation AC_Transform;
	static char* CurrentModelFilePath;
};