#ifndef SHAPE_H
#define SHAPE_H
#include "Vector.h"
#include "gl\glut.h"

class Shape
{
protected:
	Vector _transform;
	Vector _rotate;
	Vector _scale;
	const GLfloat* _diffuse;

public:
	Shape();
	Shape(Vector transform, Vector rotate, Vector scale, const GLfloat* diffuse);

	static const GLfloat white[4];
	static const GLfloat red[4];
	static const GLfloat green[4];
	static const GLfloat blue[4];

	static const GLfloat no_mat[4];
	static const GLfloat mat_ambient[4];
	static const GLfloat mat_ambient_color[4];
	static const GLfloat mat_diffuse[4];
	static const GLfloat mat_specular[4];
	static const GLfloat mat_low_spec[4];

	void translate(double x, double y, double z);
	void applyTransforms();

	void setTransform(Vector transform);
	void setRotate(Vector rotate);
	void setScale(Vector scale);

	Vector getTransform();
	Vector getRotate();
	Vector getScale();

	virtual void draw() = 0;

};

#endif