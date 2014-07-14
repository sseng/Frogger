#include "Vector.h"

Vector::Vector()
{
	_x = 0;
	_y = 0;
	_z = 0;
}

Vector::Vector(double xyz)
{
	_x = _y = _z = xyz;
}
Vector::Vector(double x, double y, double z)
{
	_x = x;
	_y = y;
	_z = z;
}