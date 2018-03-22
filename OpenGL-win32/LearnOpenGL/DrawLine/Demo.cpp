
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
		float r, g, b;	//������ָ������ɫ��glColor3f��������ȥ��Ч��
	};

	virtual void    render()
	{
		//! ָ�����µĲ������ͶӰ����
		glMatrixMode(GL_PROJECTION);
		//! ��ͶӰ��֤��ճɵ�λ����
		glLoadIdentity();
		glOrtho(0, _width, _height, 0, -100, 100);

		glColor3f(1, 1, 1);

		Vertex rect[] = {
			{ 10, 10, 0, 1, 0, 0 },
			{ 110, 10, 0, 0, 1, 0 },
			{ 10, 110, 0, 0, 0, 1 },
			{ 110, 110, 0, 1, 0, 1 },
		};

		glEnableClientState(GL_VERTEX_ARRAY);	// ����λ������
		glEnableClientState(GL_COLOR_ARRAY);	// ������ɫ����
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), rect);
		glColorPointer(3, GL_FLOAT, sizeof(Vertex), &rect[0].r);		// ����float����ʼλ����r
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