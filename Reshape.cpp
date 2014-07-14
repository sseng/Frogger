#include "gl\glut.h"

bool mode;

void reshape(int w, int h)
{
	if (h == 0) return;

	glViewport (0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (mode){
		gluPerspective (90.0, 1.0, 1.0, 60.0); // (fov y, aspect, near, far )
	}
	else{
		glOrtho(-15.0, 15.0, -15.0, 15.0, 1.0, 40.0);
	}
	//glFrustum (-1.0, 1.0, -1.0, 1.0, 0.5, 60.0); //(left, right, bottom, top, near, far)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void setMode(){
	mode = !mode;
}