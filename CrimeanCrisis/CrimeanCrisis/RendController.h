#pragma once
#include "Renderer.h"

class RendController
{
public:

	typedef struct
	{
		int width;
		int height;
		char* title;

		float field_of_view_angle;
		float z_near;
		float z_far;
	}	glutWindow;			// okno

	RendController();
	~RendController();

	static Renderer *renderer;

	//static void updateWindow();

	static void init(std::list<GraphicObject>*);
	static void display();
	static void animate(int);
	static void keyboard(unsigned char, int, int);
	static void specialKeys(int, int, int);
	static void mouse(int, int, int, int);
	static void setObject(std::list<GraphicObject>*);
	static void resize(int, int);

	static glutWindow win;
};

