#include "Sphere.h"

Sphere::Sphere(){ _radius = 1; }

Sphere::Sphere(float radius, Vector transform, Vector rotate, Vector scale, const GLfloat *diffuse): Shape(transform, rotate, scale, diffuse)
{
	_radius = radius;
}

void Sphere::setRadius(float radius){ _radius = radius; }

float Sphere::getRadius(){ return _radius; }

void Sphere::draw()
{
	_slices = 20;
	_stacks = 20;

	glPushMatrix();
		Shape::applyTransforms();
		glutSolidSphere(_radius, _slices, _stacks);
	glPopMatrix();
}