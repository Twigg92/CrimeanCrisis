#include "GraphicObject.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
GraphicObject::GraphicObject()
{
	this->TotalConnectedTriangles = 0;
	this->TotalConnectedPoints = 0;

	this->pos.x = 0.0;
	this->pos.y = 4.5;								// 4.5 ??
	this->pos.z = 0.0;

	this->box.cfp.x = this->pos.x + objLength;		// uwzglêdniæ rotacjê?
	this->box.cfp.y = this->pos.y + objWidth;
	this->box.cfl.x = this->pos.x + objLength;
	this->box.cfl.y = this->pos.y - objWidth;
	this->box.cbp.x = this->pos.x - objLength;
	this->box.cbp.y = this->pos.y + objWidth;
	this->box.cbl.x = this->pos.x - objLength;
	this->box.cbl.y = this->pos.y - objWidth;

	this->box.cRadius = glm::sqrt(abs(pos.x - this->box.cfp.x)*abs(pos.x - this->box.cfp.x) + abs(pos.y - this->box.cfp.y)*abs(pos.y - this->box.cfp.y));		// sqrt(|x-x`|^2 + |y-y`|^2)
	this->box.currentRotation = 0;

	this->rot.x = 0.0;
	this->rot.y = 0.0;
	this->rot.z = 0.0;

	this->Color[0] = 0.75;
	this->Color[1] = 1.0;
	this->Color[2] = 0.65;
	this->Color[4] = 1.0;
}

GraphicObject::GraphicObject(Vector p, Vector r, int l, int w)
{
	this->TotalConnectedTriangles = 0;
	this->TotalConnectedPoints = 0;

	this->pos.x = p.x;
	this->pos.y = p.y;
	this->pos.z = p.z;

	this->objLength = l;
	this->objWidth = w;

	this->box.cfp.x = this->pos.x + objLength;
	this->box.cfp.y = this->pos.y + objWidth;
	this->box.cfl.x = this->pos.x + objLength;
	this->box.cfl.y = this->pos.y - objWidth;
	this->box.cbp.x = this->pos.x - objLength;
	this->box.cbp.y = this->pos.y + objWidth;
	this->box.cbl.x = this->pos.x - objLength;
	this->box.cbl.y = this->pos.y - objWidth;

	this->box.fp.x = this->box.cfp.x;
	this->box.fp.y = this->box.cfp.y;
	this->box.fl.x = this->box.cfl.x;
	this->box.fl.y = this->box.cfl.y;
	this->box.bp.x = this->box.cbp.x;
	this->box.bp.y = this->box.cbp.y;
	this->box.bl.x = this->box.cbl.x;
	this->box.bl.y = this->box.cbl.y;

	//this->box.currentRotation = ...

	this->rot.x = 0.0;
	this->rot.y = 0.0;
	this->rot.z = 0.0;

	this->Color[0] = 0.75;
	this->Color[1] = 1.0;
	this->Color[2] = 0.65;
	this->Color[4] = 1.0;
}

GraphicObject::~GraphicObject()
{
}

GraphicObject GraphicObject::operator=(const GraphicObject &rhs)
{
	this->Color[0] = rhs.Color[0];
	this->Color[1] = rhs.Color[1];
	this->Color[2] = rhs.Color[2];
	this->Color[3] = rhs.Color[3];
	this->Color[4] = rhs.Color[4];

	this->OBJnormals = rhs.OBJnormals;
	this->OBJuvs = rhs.OBJuvs;
	this->OBJvertices = rhs.OBJvertices;

	this->pos.x = rhs.pos.x;
	this->pos.y = rhs.pos.y;
	this->pos.z = rhs.pos.z;

	this->box.fp = rhs.box.fp;		// this->box.fp.x = rhs.box.fp.x;	(...) ?
	this->box.fl = rhs.box.fl;
	this->box.bp = rhs.box.bp;
	this->box.bl = rhs.box.bl;

	this->rot.x = rhs.rot.x;
	this->rot.y = rhs.rot.y;
	this->rot.z = rhs.rot.z;

	this->TotalConnectedPoints;
	this->TotalConnectedTriangles;
	this->uvIndices = rhs.uvIndices;
	this->normalIndices = rhs.normalIndices;

	this->vertexIndices = rhs.vertexIndices;
	return *this;
}

bool GraphicObject::loadOBJ(const char * path, const char * texturePath)
{
	vector< glm::vec3 > temp_vertices;
	vector< glm::vec2 > temp_uvs;
	vector< glm::vec3 > temp_normals;
	TotalConnectedTriangles = 0;

	FILE * file = fopen(path, "r");
	if (file == NULL)
	{
		printf("Impossible to open the file!\n");
		return false;
	}

	while (1)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0)
		{
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertex.x /= 10; vertex.y /= 10; vertex.z /= 10;
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				printf("File can't be read by this simple parser. Try exporting with other options or check for untextured parts.\n");
				return false;
			}

			this->vertexIndices.push_back(vertexIndex[0]);
			this->vertexIndices.push_back(vertexIndex[1]);
			this->vertexIndices.push_back(vertexIndex[2]);
			this->uvIndices.push_back(uvIndex[0]);
			this->uvIndices.push_back(uvIndex[1]);
			this->uvIndices.push_back(uvIndex[2]);
			this->normalIndices.push_back(normalIndex[0]);
			this->normalIndices.push_back(normalIndex[1]);
			this->normalIndices.push_back(normalIndex[2]);

			TotalConnectedTriangles += 1;				// += 9?
		}
	}

	// Indexing..
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		vec3 vertex = temp_vertices[vertexIndex - 1];
		this->OBJvertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		vec2 uv = temp_uvs[uvIndex - 1];
		this->OBJuvs.push_back(uv);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		vec3 normal = temp_normals[normalIndex - 1];
		this->OBJnormals.push_back(normal);
	}

	printf(".OBJ file opened successfully.\n");
	//if(loadTexture(texturePath))

	printf("Texture opened successfully.\n");
	return true;
}

bool GraphicObject::loadTexture(const char* path) {
	GLuint loadBMP_custom(*path);

	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(path, "rb");
	if (!file)
	{
		printf("BMP file is not correct!\n");
		return false;
	}

	if (fread(header, 1, 54, file) != 54)
	{
		printf("BMP file is not correct!\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("BMP file is not correct!\n");
		return false;
	}

	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)
		imageSize = width*height * 3;
	if (dataPos == 0)
		dataPos = 54;

	// Create a buffer
	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);	// Read the actual data from the file into the buffer
	fclose(file);						//Everything is in memory now, the file can be closed

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return true;
}

void GraphicObject::setSize(int l, int w)
{
	this->objLength = l;
	this->objWidth = w;
}

void GraphicObject::rotateBoundingBox(float angle)
{
	//float fpArc = glm::asin(this->objWidth / this->objLength);
	//float bpArc = 180 - fpArc;
	//float flArc = 360 - fpArc;
	//float blArc = 180 + fpArc;

	//float fpAngle = this->box.currentRotation + fpArc + 90 - angle;		// k¹t obrotu dla prawej strony (arcsin() dodatni)
	//if (((fpAngle <= 90.0) && (fpAngle >= -90)) || ((fpAngle >= 270) && (fpAngle <= 360)) || ((fpAngle <= -270) && (fpAngle >= -360)))
	//{
	//	this->box.fp.x = pos.x + box.cRadius * glm::cos(fpAngle);
	//}
	//else this->box.fp.x = pos.x + box.cRadius * -glm::cos(fpAngle);		// do sprawdzenia
	//if (((fpAngle <= 0.0) && (fpAngle >= 180)) || ((fpAngle >= -360) && (fpAngle <= -180)))
	//{
	//	this->box.fp.y = pos.y + box.cRadius * glm::sin(fpAngle);
	//}
	//else this->box.fp.y = pos.y + box.cRadius * -glm::sin(fpAngle);		// do sprawdzenia

	//float flAngle = this->box.currentRotation + flArc + 90 - angle;
	//if (((flAngle <= 90.0) && (flAngle >= -90)) || ((flAngle >= 270) && (flAngle <= 360)) || ((flAngle <= -270) && (flAngle >= -360)))
	//{
	//	this->box.fl.x = pos.x + box.cRadius * glm::cos(flAngle);
	//}
	//else this->box.fl.x = pos.x + box.cRadius * -glm::cos(flAngle);		// do sprawdzenia
	//if (((flAngle <= 0.0) && (flAngle >= 180)) || ((flAngle >= -360) && (flAngle <= -180)))
	//{
	//	this->box.fl.y = pos.y + box.cRadius * glm::sin(flAngle);
	//}
	//else this->box.fl.y = pos.y + box.cRadius * -glm::sin(flAngle);		// do sprawdzenia

	//float blAngle = this->box.currentRotation + blArc + 90 - angle;
	//if (((blAngle <= 90.0) && (blAngle >= -90)) || ((blAngle >= 270) && (blAngle <= 360)) || ((blAngle <= -270) && (blAngle >= -360)))
	//{
	//	this->box.bl.x = pos.x + box.cRadius * glm::cos(blAngle);
	//}
	//else this->box.bl.x = pos.x + box.cRadius * -glm::cos(blAngle);		// do sprawdzenia
	//if (((blAngle <= 0.0) && (blAngle >= 180)) || ((blAngle >= -360) && (blAngle <= -180)))
	//{
	//	this->box.bl.y = pos.y + box.cRadius * glm::sin(blAngle);
	//}
	//else this->box.bl.y = pos.y + box.cRadius * -glm::sin(blAngle);		// do sprawdzenia

	//float bpAngle = this->box.currentRotation + bpArc + 90 - angle;
	//if (((bpAngle <= 90.0) && (bpAngle >= -90)) || ((bpAngle >= 270) && (bpAngle <= 360)) || ((bpAngle <= -270) && (bpAngle >= -360)))
	//{
	//	this->box.bp.x = pos.x + box.cRadius * glm::cos(bpAngle);
	//}
	//else this->box.bp.x = pos.x + box.cRadius * -glm::cos(bpAngle);		// do sprawdzenia
	//if (((bpAngle <= 0.0) && (bpAngle >= 180)) || ((bpAngle >= -360) && (bpAngle <= -180)))
	//{
	//	this->box.bp.y = pos.y + box.cRadius * glm::sin(bpAngle);
	//}
	//else this->box.bp.y = pos.y + box.cRadius * -glm::sin(bpAngle);		// do sprawdzenia

	//this->box.currentRotation += angle;				// updating current rotation angle
}

void GraphicObject::SetDisplay()
{
	loadTexture("grafiki/tex1.bmp");
	// !!! TESTING AREA !!!
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, OBJvertices.size() * sizeof(glm::vec3), &OBJvertices[0], GL_STATIC_DRAW);
}

void GraphicObject::Draw()
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(rot.x, rot.y, rot.z, 2);
	glColor3fv(Color);

	// !!! TESTING AREA !!!

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, this->TotalConnectedTriangles * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);

	GLfloat defaultAmbient[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat defaultDiffuse[] = { 0.8, 0.8, 0.8, 1 };
	GLfloat defaultSpecular[] = { 0, 0, 0, 1 };
	GLfloat defaultShininess = 0;
	GLfloat defaultEmission[] = { 0, 0, 0, 1 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, defaultAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, defaultDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, defaultSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, defaultShininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, defaultEmission);

	glPopMatrix();
}