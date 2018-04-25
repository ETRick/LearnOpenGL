
#include <windows.h>
#include <tchar.h>
#include <math.h>
#include "CELLMath.hpp"
#include<gl/glu.h>
#include "OpenGLWindow.h"
#include <vector>
using namespace CELL;

struct Vertex {
	unsigned char r, g, b, a;//usigned char 2 字节
	float x, y, z;			// float 4字节
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

		Vertex cubeVertices[] =
		{
			{ 255,0,0,255, -1.0f,-1.0f, 1.0f },
			{ 255,0,0,255, 1.0f,-1.0f, 1.0f },
			{ 255,0,0,255, 1.0f, 1.0f, 1.0f },
			{ 255,0,0,255, -1.0f, 1.0f, 1.0f },

			{ 0,255,0,255, -1.0f,-1.0f,-1.0f },
			{ 0,255,0,255, -1.0f, 1.0f,-1.0f },
			{ 0,255,0,255, 1.0f, 1.0f,-1.0f },
			{ 0,255,0,255, 1.0f,-1.0f,-1.0f },

			{ 0,0,255,255, -1.0f, 1.0f,-1.0f },
			{ 0,0,255,255, -1.0f, 1.0f, 1.0f },
			{ 0,0,255,255, 1.0f, 1.0f, 1.0f },
			{ 0,0,255,255, 1.0f, 1.0f,-1.0f },

			{ 0,255,255,255, -1.0f,-1.0f,-1.0f },
			{ 0,255,255,255, 1.0f,-1.0f,-1.0f },
			{ 0,255,255,255, 1.0f,-1.0f, 1.0f },
			{ 0,255,255,255, -1.0f,-1.0f, 1.0f },

			{ 255,0,255,255, 1.0f,-1.0f,-1.0f },
			{ 255,0,255,255, 1.0f, 1.0f,-1.0f },
			{ 255,0,255,255, 1.0f, 1.0f, 1.0f },
			{ 255,0,255,255, 1.0f,-1.0f, 1.0f },

			{ 255,255,255,255, -1.0f,-1.0f,-1.0f },
			{ 255,255,255,255, -1.0f,-1.0f, 1.0f },
			{ 255,255,255,255, -1.0f, 1.0f, 1.0f },
			{ 255,255,255,255, -1.0f, 1.0f,-1.0f }
		};

		for (int i = 0; i < sizeof(cubeVertices) / sizeof(cubeVertices[0]); ++i)
		{
			cubeVertices[i].z -= 5;
		}

#if 1
		// 启用深度测试
		glEnable(GL_DEPTH_TEST);
		//Vertex必须和GL_C4UB_V3F color 4 unsigned byte vertex 3 float 严格匹配
		//Vertex 定点定义放颜色前面就不行了
		glInterleavedArrays(GL_C4UB_V3F, 0, cubeVertices);
#else

		glEnable(GL_DEPTH_TEST);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &cubeVertices[0].x);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), cubeVertices);
#endif
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