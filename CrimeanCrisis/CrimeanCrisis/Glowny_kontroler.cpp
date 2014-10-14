#include "Glowny_kontroler.h"

Glowny_kontroler::Glowny_kontroler()
{
	_sound = new Sound();
	_sound->LoadSounds();
	_objects = new std::list<GraphicObject>();
}


Glowny_kontroler::~Glowny_kontroler()
{
	delete _sound;
	_objects->clear();
	delete _objects;
}

void Glowny_kontroler::Start() 
{
	GraphicObject obj;	
	obj.loadOBJ("models/megahuge_t1.obj", "grafiki/tex1.bmp");
	obj.pos.z = 0.0;						// czołg nie unosi sie w powietrzu - czemu nie jest widoczny na początku domyślcie sie sami (bo ja nie mam zielonego pojęcia) (-20.0)
	obj.Color[0] = 0.0;						// zmiana koloru czołgu - dla celów testowych

	// TESTING AREA !!!
	GraphicObject test_obj_1;		// fioletowy
	test_obj_1.loadOBJ("models/megahuge_t1.obj", "grafiki/tex1.bmp");
	test_obj_1.pos.x = 30.0;
	test_obj_1.pos.y = 10.0;
//	test_obj_1.pos.z = 10.0;
	test_obj_1.Color[1] = 0.5;

	GraphicObject test_obj_2;		// szary
	test_obj_2.loadOBJ("models/megahuge_t1.obj", "grafiki/tex1.bmp");
	test_obj_2.pos.x = -1.488228;
	test_obj_2.pos.y = 3.262749;
//	test_obj_2.pos.z = 10.0;
	test_obj_2.Color[2] = 1.0;

	RendController::init(_objects);
	obj.SetDisplay();
	_objects->push_back(obj);

	// TESTING
	test_obj_1.SetDisplay();
	_objects->push_back(test_obj_1);
	test_obj_2.SetDisplay();
	_objects->push_back(test_obj_2);
		

	//static const GLfloat g_vertex_buffer_data[] = {
	//	-100.0f, -100.0f, 10.0f,
	//	100.0f, 100.0f, 10.0f,
	//	-100.0f, 100.0f, 10.0f,
	//	-100.0f, -100.0f, 10.0f,
	//	100.0f, 100.0f, 10.0f,
	//	100.0f, -100.0f, 10.0f,
	//};
	//
	//GLuint vertexbuffer;
	//glGenBuffers(1, &vertexbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices total -> 1 triangle
	//glDisableVertexAttribArray(0);
	glutMainLoop();


	//bool the_end = false;
	//GameServer server;
	//Klient klient(_objects);
	////poniższy kod odpowiada za uruchomienie serwera i klienta
	////std::thread first(&GameServer::Start, server);
	////std::thread second(&Klient::Start, klient);
	////first.join();
	////second.join();
}