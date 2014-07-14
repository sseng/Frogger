#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>

using namespace std;

class Vector
{
private:
	double _x, _y, _z;
public:
	Vector();
	Vector(double xyz);
	Vector(double x, double y, double z);
	
	void setX(double x){ _x = x; }; 
	void setY(double y){ _y = y; };
	void setZ(double z){ _z = z; };

	double getX(){ return _x; };
	double getY(){ return _y; };
	double getZ(){ return _z; };

};
#endif