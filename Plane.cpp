#include "Plane.h"

GLuint _texture;

Plane::Plane()
{
	_p1 = Vector(-0.5, -0.5, 0);
	_p2 = Vector( 0.5,  0.5, 0);
}

Plane::Plane(Vector p1, Vector p2, Vector transform, Vector rotate, Vector scale, const GLfloat *diffuse): Shape(transform, rotate, scale, diffuse)
{
	_p1 = p1;
	_p2 = p2;
}

void Plane::draw()
{		
	glPushMatrix();		
		Plane::applyTransforms();
		glBegin(GL_POLYGON);
			glTexCoord2d(0.0, 0.25);	glVertex3d(_p1.getX(), _p1.getY(), _p1.getZ()); //x1, y1
			glTexCoord2d(1.0, 0.25);	glVertex3d(_p2.getX(), _p1.getY(), _p1.getZ()); //x2, y1
			glTexCoord2d(1.0, 0.75);	glVertex3d(_p2.getX(), _p2.getY(), _p2.getZ()); //x2, y2
			glTexCoord2d(0.0, 0.75);	glVertex3d(_p1.getX(), _p2.getY(), _p2.getZ()); //x1, y2
		glEnd();	
	glPopMatrix();
}
