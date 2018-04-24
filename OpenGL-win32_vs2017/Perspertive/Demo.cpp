
#include <windows.h>
#include <tchar.h>
#include <math.h>
#include "CELLMath.hpp"
#include "OpenGLWindow.h"
#include <gl/glu.h>
#include <vector>
using namespace CELL;

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

		float3  arVert[] =
		{
			float3(0.5f,0,-0.5),
			float3(0.2f,0.3,-.5),
			float3(0.8f,0.3,-.5),
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(float3), arVert);
		glDrawArrays(GL_TRIANGLES, 0, 3);
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