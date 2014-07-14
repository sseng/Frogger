#include "Cube.h"

Cube::Cube()
{
	_size = 1;
}

Cube::Cube(float size, Vector transform, Vector rotate, Vector scale, const GLfloat *diffuse): Shape(transform, rotate, scale, diffuse)
{
	_size = size;
}

void Cube::draw()
{
	glPushMatrix();
		Shape::applyTransforms();
		glutSolidCube(_size);
	glPopMatrix();
}