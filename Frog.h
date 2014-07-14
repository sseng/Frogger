#ifndef FROG_H
#define FROG_H
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "Shape.h"
#include "glm.h"

class Frog: public Shape
{
private:	
	GLMmodel* pmodel;

public:
	Frog();
	Frog(Vector transform, Vector rotate, Vector scale, const GLfloat* diffuse);
	void drawModel();
	void draw();

};
#endif