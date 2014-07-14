#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include"gl\glut.h"
#include "Cube.h"
#include "Plane.h"
#include "Sphere.h"
#include "glm.h"

using namespace std;

void		cars(int start, int end, double height, double speed);
void		drawCars();
void		drawFrog();
void		drawModel();
void		showColor();
void		FreeTexture(GLuint texture);
void		street();
void		river();
void		setColor();
void		setMode();

GLuint		LoadTexture(const char * filename, int width, int height);
GLuint		getTexture();
int			_frog = 0;
int			moveX, moveY;
bool		colorOn = true;
GLMmodel*	pmodel;
GLuint		texture;
int			color;
float eyeX		= 0.0;
float eyeY		= 0.0;
float eyeZ		= 10.0;
float centerX	= 0.0;
float centerY	= 0.0;
float centerZ	= 0.0;

const GLfloat red[4] = {1.0, 0.0, 0.0, 1.0 };
const GLfloat green[4] = {0.0, 1.0, 0.0, 1.0 };
const GLfloat blue[4] = {0.0, 0.0, 1.0, 1.0 };

//vector<Shape*> player;
vector<Shape*> obstacles;

struct player{
	int		x;
	int		y;
	bool	isActive;
}frog[5];

void display()
{
	glClearColor (0.0, 0.0, 0.0, 1.0);	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	
	gluLookAt (	eyeX, eyeY, eyeZ, 
				centerX, centerY, centerZ, 
				0.0, 1.0, 0.0 );

	drawFrog();
	street();
	drawCars();
	river();

	glFlush();
	glutSwapBuffers();
}
void drawCars()
{
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		texture = LoadTexture("car_64.raw", 64, 64);
		cars( 0,  4, -10,  0.005);
		cars( 4,  7,  -8,  0.035);
		cars( 7, 10,  -6,  0.017);
		cars(10, 13,  -4, -0.065);
		cars(13, 14,  -2, -0.150);
		cars(14, 18,   0, -0.020);
		FreeTexture(texture);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void drawFrog()
{	
	//Shape *frog;	
	/*Vector startLoc(0.0, -12.0, 0.0);
	Vector rotate(0);
	Vector scale(1);
	frog = new Frog(startLoc, rotate, scale, Shape::green);	 
	player.push_back(frog);
	player.at(0)->draw();*/	

	glPushMatrix();
		glTranslatef(frog[_frog].x, frog[_frog].y, 0);
		glTranslatef(0, -13, 1);
		glScalef(0.75f, 0.75f, 0.75f);
		glRotatef(180, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
		drawModel();
	glPopMatrix();
	frog[_frog].isActive = true;
}
void drawModel()
{
	if (!pmodel){
		pmodel = glmReadOBJ("frog2.obj");
		if (!pmodel) exit(0);
		glmUnitize(pmodel);
		glmFacetNormals(pmodel);
		glmVertexNormals(pmodel, 90.0);
	}
	glmDraw(pmodel, GLM_SMOOTH );
}
void animate()
{
	glutPostRedisplay();
}
void showColor()
{
	if (colorOn){
		glEnable(GL_LIGHTING);
	}
	else{
		glDisable(GL_LIGHTING);
	}
}
GLuint LoadTexture(const char * filename, int width, int height)
{
	GLuint texture;
    unsigned char * data;
    FILE * file;

    //The following code will read in our RAW file
    file = fopen( filename,"rb" );
    if ( file == NULL ){
		return 0;
	}
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );

    glGenTextures( 1, &texture ); //generate the texture with the loaded data
    glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture to it’s array
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //set texture environment parameters

    //here we are setting what textures to use and when. The MIN filter is which quality to show
    //when the texture is near the view, and the MAG filter is which quality to show when the texture
    //is far from the view.

    //The qualities are (in order from worst to best)
    //GL_NEAREST
    //GL_LINEAR
    //GL_LINEAR_MIPMAP_NEAREST
    //GL_LINEAR_MIPMAP_LINEAR

    //And if you go and use extensions, you can use Anisotropic filtering textures which are of an
    //even better quality, but this will do for now.
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    //Here we are setting the parameter to repeat the texture instead of clamping the texture
    //to the edge of our shape. 
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    //Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    free( data ); //free the texture
    return texture; //return whether it was successfull
}
void FreeTexture(GLuint texture){ glDeleteTextures( 1, &texture ); }
void street() 
{
	glPushMatrix();		
		texture = LoadTexture("street.raw", 512, 512);
		glTranslatef(0, 0, -1);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glBindTexture(GL_TEXTURE_2D, texture); //bind our texture to our shape
		glBegin (GL_QUADS);
			glTexCoord2d(0.0,0.0); glVertex2d(-16.0,-11.0); //with our vertices we have to assign a texcoord
			glTexCoord2d(1.0,0.0); glVertex2d( 16.0,-11.0); //so that our texture has some points to draw to
			glTexCoord2d(1.0,1.0); glVertex2d( 16.0,  1.0);
			glTexCoord2d(0.0,1.0); glVertex2d(-16.0,  1.0);
		glEnd();
		FreeTexture(texture);		
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();	
}
void river()
{
	glPushMatrix();
		Shape* river;
		Vector startLoc(0.0, 0.0, 0.0);
		Vector rotate(0);
		Vector scale(1);
		
		//glEnable(GL_LIGHTING);
		showColor();
		//glBindTexture(GL_TEXTURE_2D, texture); //bind our texture to our shape
		//glBegin (GL_QUADS);
		//	glTexCoord2d(0.0,0.0); glVertex2d(-16.0,-11.0); //with our vertices we have to assign a texcoord
		//	glTexCoord2d(1.0,0.0); glVertex2d( 16.0,-11.0); //so that our texture has some points to draw to
		//	glTexCoord2d(1.0,1.0); glVertex2d( 16.0,  1.0);
		//	glTexCoord2d(0.0,1.0); glVertex2d(-16.0,  1.0);
		//glEnd();
		river = new Plane(Vector(-16,1,-1), Vector(16,12,-1), startLoc, rotate, scale, Shape::blue);
		river->draw();
	glPopMatrix();	
}
void cars(int start, int end, double height, double speed)
{
	Shape *car;
	Vector XYZ1(-1.0, -0.5, 0);
	Vector XYZ2(1, 0.5, 0);
	Vector rotate(0);
	Vector scale(0);
	
	for (int i = start; i < end; i++){
		for (int j = 0; j < (end - start); j++){

			Vector placement(5*j, height, 0);			
			glBindTexture(GL_TEXTURE_2D, texture);
			
			car = new Plane(XYZ1, XYZ2, placement, rotate, scale, Shape::red);
			obstacles.push_back(car);
			obstacles[i]->draw();			
			obstacles[i]->translate(speed, 0, 0);

			if (speed > 0 && obstacles[i]->getTransform().getX() >= 16){
				obstacles[i]->setTransform(Vector(-16.0, height, 0));
				obstacles[i]->setScale(Vector(2));
			}
			else if (speed < 0 && obstacles[i]->getTransform().getX() <= -16){
				obstacles[i]->setTransform(Vector(16.0, height, 0));
				obstacles[i]->setScale(Vector(2));
			}			
		}
	}
}
void setColor()
{
	if (color = 0){
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Shape::red);
		color = 1;
	}
	if (color = 1){
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Shape::green);
		color = 2;
	}
	if (color = 2){
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Shape::blue);
		color = 0;
	}
	
}
void controls(unsigned char key, int x, int y)
{	
	//int		frog = _frog;		
	int xPos = frog[_frog].x;
	int yPos = frog[_frog].y;
	cout << "xPos: " << xPos << " yPos: " << yPos << endl;

	switch (key){
	case 27: exit(0);break;
	case 'a': 	
		if (frog[_frog].isActive == true && xPos != -13){ 
			frog[_frog].x -= 1;
		}
		break;
	case 'd': 
		if (frog[_frog].isActive == true && xPos != 13){ 
			frog[_frog].x += 1;
		}
		break;
	case 'w': 
		if (frog[_frog].isActive == true && yPos != 26){ 
			frog[_frog].y += 1;
		}
		break;
	case 's':
		if (frog[_frog].isActive == true && yPos != 0){ 
			frog[_frog].y -= 1;
		}
		break;
	case 'r': eyeY = eyeX = 0.0; break;
	case '1': colorOn = !colorOn; break;
	case '2': glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
	case '3': glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;
	case '4': glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
	case '5': setColor(); break;
	case '6': setMode(); break;

	}
	/*double	xPos = player[frog]->getTransform().getX();
	double	yPos = player[frog]->getTransform().getY();
	double	distance = 2;
	cout << "xPos: " << xPos << " yPos: " << yPos << endl;
	
	case 'a': if ( !player.empty() && xPos != -12){
			player[frog]->translate(-distance, 0, 0);
		}break;
	case 'd': if ( !player.empty() && xPos != 12){
			player[frog]->translate(distance, 0, 0);
		}break;
	case 'w': if ( !player.empty() && yPos != 12){
			player[frog]->translate(0, distance, 0);
		}break;
	case 's': if ( !player.empty() && yPos != -12){
			player[frog]->translate(0, -distance, 0);
		}break;
	case '1': colorOn = !colorOn;		
		break;
	*/
	glutPostRedisplay();
}
void specialKeyboardHandler(int key, int x, int y)
{
	int xPos = frog[_frog].x;
	int yPos = frog[_frog].y;

	switch (key)
	{
		case GLUT_KEY_LEFT:	
			if (frog[_frog].isActive == true && xPos != -13){
				frog[_frog].x -= 1;
			}
			break;
		case GLUT_KEY_RIGHT:
			if (frog[_frog].isActive == true && xPos != 13){
				frog[_frog].x += 1;
			}
			break;
		case GLUT_KEY_UP: 
			if (frog[_frog].isActive == true && yPos != 26){
				frog[_frog].y += 1;
			}
			break;
		case GLUT_KEY_DOWN: 
			if (frog[_frog].isActive == true && yPos != 0){
				frog[_frog].y -= 1;
			}
			break;
	}
	glutPostRedisplay();
}
