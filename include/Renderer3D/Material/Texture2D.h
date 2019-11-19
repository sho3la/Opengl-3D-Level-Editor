#pragma once

class Texture2D
{
public:
	Texture2D(const char* texture_filename);

	~Texture2D();

	int width;

	int height;

	int nrChannels;

	unsigned char *data;

	unsigned int GLtexture = 0;
};