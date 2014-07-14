#include <iostream>
#include <gl\glut.h>

using namespace std;

void moveFrog(char direction, double distance);

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
			exit(0);
			break;
		case '1': //solid
			//setRenderType(0);
			cout << "set type to 0" << endl;
			break;
		case '2': //wireframe
			//setRenderType(1);
			cout << "set type to 1" << endl;
			break;
		case '3': //color
			//showColor();
			break;

		case 'a': moveFrog('l', 0.5); 
			break;
		case 'd': moveFrog('r', 0.5); 
			break;
		case 'w': moveFrog('u', 0.5); 
			break;
		case 's': moveFrog('d', 0.5); 
			break;
			
	}
	glutPostRedisplay();
}