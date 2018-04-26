
#include <windows.h>
#include <tchar.h>
#include <math.h>
#include "CELLMath.hpp"
#include<gl/glu.h>
#include "OpenGLWindow.h"
#include <vector>
using namespace CELL;
/*
三个重要的矩阵：
调用glMatrixMode，将当前矩阵设为对应的矩阵，一般跟`glLoadIdentity()` 来将矩阵变为单位矩阵
glMatrixMode(GL_TEXTURE)
glMatrixMode(GL_PROJECTION)
glMatrixMode(GL_MODELVIEW)
*/

struct Vertex {
	unsigned char r, g, b, a;//usigned char 2 字节
	float x, y, z;			// float 4字节
};

class   Demo :public OpenGLWindow
{
public:

	float   _angle;
	float   _angleMoon;
	float   _angleEarth;

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

		// 改为模型空间
		glMatrixMode(GL_MODELVIEW);
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

#if 0
		_angle += 1;
		//! 太阳
		glLoadIdentity();
		glTranslatef(0, -10, -150);
		glScalef(2, 2, 2);
		glRotatef(_angle, 0, 1, 0);

		glDrawArrays(GL_QUADS, 0, 24);

		// 太阳变换的矩阵仍在上下文中，接下去都是继续对这个矩阵做操作
		//! 地球
		_angleEarth += 3;
		glRotatef(_angleEarth, 0, 1, 0);
		glTranslatef(0, 0, -50);
		glScalef(0.5, 0.5, 0.5);
		glRotatef(_angle, 0, 1, 0);
		glDrawArrays(GL_QUADS, 0, 24);

		//! 月球
		_angleMoon += 10;
		glRotatef(_angleMoon, 0, 1, 0);
		glTranslatef(0, 0, -10);
		glScalef(0.5, 0.5, 0.5);
		glRotatef(_angle, 0, 1, 0);
		glDrawArrays(GL_QUADS, 0, 24);
#else
		// 这里显示地进行了矩阵运算，更容易理解
		_angle += 1;

		CELL::matrix4   matSun;
		CELL::matrix4   matSunTrans;
		CELL::matrix4   matSunScale;
		CELL::matrix4   matSunRot;
		matSunRot.rotate(_angle, CELL::float3(0, 1, 0));
		matSunTrans.translate(0, -10, -150);
		matSunScale.scale(2, 2, 2);

		matSun = matSunTrans * matSunScale * matSunRot;

		glLoadMatrixf(matSun.data());

		glDrawArrays(GL_QUADS, 0, 24);


		CELL::matrix4   matEarth;
		CELL::matrix4   matEarTrans;
		CELL::matrix4   matEarScale;
		CELL::matrix4   matEarRot;

		matEarRot.rotate(_angleEarth, CELL::float3(0, 1, 0));
		matEarTrans.translate(0, 0, -50);
		matEarScale.scale(0.5f, 0.5f, 0.5f);

		matEarth = matSun * matEarTrans * matEarScale * matEarRot;

		glLoadMatrixf(matEarth.data());

		_angleEarth += 3;
		glDrawArrays(GL_QUADS, 0, 24);
		_angleMoon += 10;

		glRotatef(_angleMoon, 0, 1, 0);
		glTranslatef(0, 0, -10);
		glScalef(0.5, 0.5, 0.5);
		glRotatef(_angle, 0, 1, 0);
		glDrawArrays(GL_QUADS, 0, 24);
#endif
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