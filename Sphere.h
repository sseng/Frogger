#ifndef SPHERE_H
#define SPHERE_H
#include "Shape.h"

class Sphere : public Shape
{
private:
	float _radius;
	int _slices, _stacks;
public: 
	Sphere();
	Sphere(float radius, Vector transform, Vector rotate, Vector scale, const GLfloat *diffuse);

	void setSlices(int slice);
	void setStacks(int stack);
	void setRadius(float radius);
	float getRadius();

	void draw();
};
#endif