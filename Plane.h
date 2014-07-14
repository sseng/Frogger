#ifndef PLANE_H
#define PLANE_H
#include "Shape.h"

class Plane: public Shape
{
private:
	Vector _p1;
	Vector _p2;	

public:
	Plane();
	Plane(Vector p1, Vector p2, Vector transform, Vector rotate, Vector scale, const GLfloat* diffuse);	
	void draw();

};
#endif