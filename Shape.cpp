#include "Shape.h"

const GLfloat Shape::white[4] = {1.0, 1.0, 1.0, 1.0 };
const GLfloat Shape::red[4] = {1.0, 0.0, 0.0, 1.0 };
const GLfloat Shape::green[4] = {0.0, 1.0, 0.0, 1.0 };
const GLfloat Shape::blue[4] = {0.0, 0.0, 1.0, 1.0 };

const GLfloat Shape::no_mat[4] = { 0.1, 0.1, 0.1, 1.0 };
const GLfloat Shape::mat_ambient[4] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat Shape::mat_ambient_color[4] = { 0.8, 0.8, 0.2, 1.0 };
const GLfloat Shape::mat_diffuse[4] = { 0.1, 0.5, 0.8, 1.0 };
const GLfloat Shape::mat_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat Shape::mat_low_spec[4] = { 0.25, 0.25, 0.25, 1.0 };

Shape::Shape()
{
	_scale.setX(1);
	_scale.setY(1);
	_scale.setZ(1);
	_diffuse = white;
}

Shape::Shape(Vector transform, Vector rotate, Vector scale, const GLfloat* diffuse)
{
	_transform = transform;
	_rotate = rotate;
	_scale = scale;
	_diffuse = diffuse;
}

void Shape::translate(double x, double y, double z)
{
	_transform.setX( _transform.getX() + x );
	_transform.setY( _transform.getY() + y );
	_transform.setZ( _transform.getZ() + z );
}

void Shape::applyTransforms()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_low_spec);
	glTranslatef(_transform.getX(), _transform.getY(), _transform.getZ());
	glRotatef(_rotate.getX(), 1, 0, 0);
	glRotatef(_rotate.getY(), 0, 1, 0);
	glRotatef(_rotate.getZ(), 0, 0, 1);
	glScalef(_scale.getX(), _scale.getY(), _scale.getZ());
}

void Shape::setTransform(Vector transform){ _transform = transform; }
void Shape::setRotate(Vector rotate){ _rotate = rotate; }
void Shape::setScale(Vector scale){ _scale = scale; }

Vector Shape::getTransform(){ return _transform; }
Vector Shape::getRotate(){ return _rotate; }
Vector Shape::getScale(){ return _scale; }


