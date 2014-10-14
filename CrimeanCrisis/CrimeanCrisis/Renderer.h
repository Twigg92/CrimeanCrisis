#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define CUT_PARAM 10.0f
//#define GLEW_STATIC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "lib/GL/glew.h"
#include "lib/GLFW/glfw3.h"
#include "lib/GL/glut.h"
#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"
#include "GraphicObject.h"
#include "Types.h"
#include "Units.h"
#include "Rain.h"
#include "UI.h"
#include "MainMenu.h"
#include "ServerMenu.h"

enum Screen
{
	MainMenuScreen,
	ServerMenuScreen,
	GameScreen
};

class Renderer
{
public:
	Renderer();
	Renderer(std::list<GraphicObject>*);
	~Renderer();

	typedef struct
	{
		int width;
		int height;
		char* title;

		float field_of_view_angle;
		float z_near;
		float z_far;
	}	glutWindow;			// okno

	//void updateWindow();

	void init();
	void display();
	void keyboard(unsigned char, int, int);
	void specialKeys(int, int, int);
	void mouse(int, int, int, int);
	void resize(int, int);
	void animate();
	void set3D(int w, int h);
	void set2D(int w, int h);
	void prepareToSelection();				// must be used if camera setting have changed
	void pick();

	void defaultMaterial();
	void drawBulb(Light light);
	void setLight(Light light);

	//accessors
	GraphicObject* GetPlain() { return plain; }
	bool IsRaining() { return isRaining; }

	glutWindow win;

	// ray casting
	void intersectionWithXyPlane(float* worldPos);
	Vector getClickPosInWorld();
	Vector getDirection();
	
	// ray casting
	Vector clickPosInWorld;		// two points describing picking ray
	Vector rayDirection;
	Vector screenHoritzontally;
	Vector screenVertically;
	float* point;

private:
	Screen screen;
	int x1, x2, y1, y2;								// wspó³rzêdne kursora
	int map_x1, map_x2, map_y1, map_y2;				// wspó³rzêdne na mapie
	//GLFWwindow *window;
	//float g_rotation;
	std::list<GraphicObject> *objList;			// jednostka (lista jednostek)
	GraphicObject *plain;		// mapa

	Vector cam;					// po³o¿enie kamery
	Vector dir;					// ukierunkowanie kamery
	
	Vector camView;				// viewing direction
	Vector up;
	Vector camPos;					// TESTING
	//Vector lookAt;

	float nearParam, farParam,
		leftParam, rightParam,
		topParam, bottomParam;

	bool mousePressed;

	Light* sun;
	Rain* rain;
	GameUI * gameUI;
	MainMenu * mainMenu;
	ServerMenu * serverMenu;

	// roboczo
	bool inGame;
	bool isRaining;

	void displayGameScreen();
	void displayMainMenuScreen();
	void displayServerMenuScreen();


};