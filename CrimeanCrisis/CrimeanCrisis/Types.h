#ifndef _TYPES_H_
#define _TYPES_H_

#include <Windows.h>
#include <math.h>
#include "lib/GL/GL.h"
// Structure representing point or vector in 3D space
class Vector
{
public:
	float x, y, z;

	Vector();
	Vector(const Vector &p);
	Vector(float x, float y, float z);
	Vector(float tab[], int count);
	operator float* ();

	float dot(Vector arg);
	Vector cross(Vector arg);

	void add(Vector a);
	void sub(Vector a);
	void set(Vector a);
	void normalize();
	void scale(float s);
	void crossAndAssign(Vector a, Vector b);
	void subAndAssign(Vector a, Vector b);	
	float l2norm();
};

// Structure representing RGB/RGBA color
class Color 
{
public:
	float r, g, b, a;

	Color();
	Color(const Color &c);
	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);
	Color(float tab[], int count);
	operator float* ();

};

#endif