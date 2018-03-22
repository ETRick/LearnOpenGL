
#include <windows.h>
#include <tchar.h>
#include <math.h>

#include "OpenGLWindow.h"
#define M_PI (3.14159265358979323846)

class   Demo :public OpenGLWindow
{
public:

	struct Vertex {
		float x, y, z;
		float r, g, b;	//顶点里指定了颜色，glColor3f函数就是去了效果
	};

	virtual void    render()
	{
		//! 指定以下的操作针对投影矩阵
		glMatrixMode(GL_PROJECTION);
		//! 将投影举证清空成单位矩阵
		glLoadIdentity();
		glOrtho(0, _width, _height, 0, -100, 100);

		glColor3f(1, 1, 1);

		Vertex rect[] = {
			{ 10, 10, 0, 1, 0, 0 },
			{ 110, 10, 0, 0, 1, 0 },
			{ 10, 110, 0, 0, 0, 1 },
			{ 110, 110, 0, 1, 0, 1 },
		};

		glEnableClientState(GL_VERTEX_ARRAY);	// 启用位置数组
		glEnableClientState(GL_COLOR_ARRAY);	// 启用颜色数组
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), rect);
		glColorPointer(3, GL_FLOAT, sizeof(Vertex), &rect[0].r);		// 三个float，起始位置是r
		glDrawArrays(GL_LINE_LOOP, 0, 4); // GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP
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