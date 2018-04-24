
#include <windows.h>
#include <tchar.h>
#include <math.h>
#include "CELLMath.hpp"
#include<gl/glu.h>
#include "OpenGLWindow.h"
#include <vector>
using namespace CELL;

struct Vertex {
	float x, y, z;
};

class   Demo :public OpenGLWindow
{
public:
	Demo()
	{
	}

	virtual void    render()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(60, double(_width) / double(_height), 0.1, 1000);

		Vertex cubeVertices[] = {
			{ -1.0f,-1.0f,  1.0f },
			{ 1.0f, -1.0f,  1.0f },
			{ 1.0f, 1.0f,   1.0f },
			{ -1.0f, 1.0f,  1.0f },

			{ -1.0f,-1.0f,  -1.0f },
			{ -1.0f, 1.0f,  -1.0f },
			{ 1.0f, 1.0f,   -1.0f },
			{ 1.0f,-1.0f,   -1.0f },

			{ -1.0f, 1.0f,  -1.0f },
			{ -1.0f, 1.0f,  1.0f },
			{ 1.0f, 1.0f,   1.0f },
			{ 1.0f, 1.0f,   -1.0f },

			{ -1.0f,-1.0f,  -1.0f },
			{ 1.0f,-1.0f,   -1.0f },
			{ 1.0f,-1.0f,   1.0f },
			{ -1.0f,-1.0f,  1.0f },

			{ 1.0f,-1.0f,  -1.0f },
			{ 1.0f, 1.0f,  -1.0f },
			{ 1.0f, 1.0f,  1.0f },
			{ 1.0f,-1.0f,  1.0f },

			{ -1.0f,-1.0f,  -1.0f },
			{ -1.0f,-1.0f,  1.0f },
			{ -1.0f, 1.0f,  1.0f },
			{ -1.0f, 1.0f,  -1.0f }
		};
		for (int i = 0; i < sizeof(cubeVertices) / sizeof(cubeVertices[0]); ++i)
		{
			cubeVertices[i].z -= 5;
		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), cubeVertices);
		glDrawArrays(GL_QUADS, 0, 24);
	}
};

int __stdcall WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
)
{

	Demo    instance;
	instance.main(800, 600);


	return  0;
}