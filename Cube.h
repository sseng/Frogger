#ifndef CUBE_H
#define CUBE_H
#include "Shape.h"

class Cube: public Shape
{
private:
	float _size;

public:
	Cube();
	Cube(float size, Vector transform, Vector rotate, Vector scale, const GLfloat* diffuse);

	void setSize(float size);
	float getSize();
	void draw();
};
#endif