#ifndef _UNITS_H_
#define _UNITS_H_

#include "Types.h"

// Class representing OpenGL light settings
class Light 
{
private:
	int number;
	Vector pos;
	Vector dir;
	float attenuation[3];
	float cutoff;
	float exponent;

	void initAttenuation();
	void initCutoff();
	void initExponent();

public:
	Light();
	Light(int number, Vector pos);
	Light(int number, Vector pos, Vector dir);
	Light(int number, Vector pos, Vector dir, float* attenuation);
	Light(int number, Vector pos, Vector dir, float cutoff, float exponent);
	Light(int number, Vector pos, Vector dir, float* attenuation, float cutoff, float exponent);

	int getNumber();
	Vector getPos();
	Vector getDir();
	float getAttenuation(int i);
	float getCutoff();
	float getExponent();

	void setNumber(int mode);
	void setPos(Vector pos);
	void setPos(float* pos);
	void setDir(Vector dir);
	void setDir(float* dir);
	void setAttenuation(int mode, float attenuation);
	void setCutoff(float cutoff);
	void setExponent(float exponent);

	void modifyAttenuation(int mode, float change);
	void modifyCutoff(float change);
	void modifyExponent(float change);
};

#endif