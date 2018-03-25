
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
	};

	Vertex _line[360];


	virtual void    render()
	{
		//! 指定以下的操作针对投影矩阵
		glMatrixMode(GL_PROJECTION);
		//! 将投影举证清空成单位矩阵
		glLoadIdentity();
		glOrtho(0, _width, _height, 0, -100, 100);

		glColor3f(1, 1, 1);

		Vertex p0 = { 10, 10, 0 };
		Vertex p1 = { 100, 10, 0 };
		Vertex p2 = { 50, 100, 0 };

		int index = 0;
		for (float t = 0; t < 1.0; t += 0.01, ++index) {
			_line[index].x = (1 - t)*(1 - t)*p0.x + 2 * t * (1 - t)*p1.x + t*t*p2.x;
			_line[index].y = (1 - t)*(1 - t)*p0.y + 2 * t * (1 - t)*p1.y + t*t*p2.y;
			_line[index].z = 0;
		}

		glEnableClientState(GL_VERTEX_ARRAY);	// 启用位置数组
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), _line);
		glDrawArrays(GL_LINE_STRIP, 0, index - 1); // GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP
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