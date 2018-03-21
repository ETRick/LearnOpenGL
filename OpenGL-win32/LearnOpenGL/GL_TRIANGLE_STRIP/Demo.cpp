
#include <windows.h>
#include <tchar.h>
#include <math.h>

#include "OpenGLWindow.h"
#define M_PI (3.14159265358979323846)

/*
OPENGL_�����δ�GL_TRIANGLE_STRIP���
http://blog.csdn.net/onafioo/article/details/39454233
*/

class   Demo :public OpenGLWindow
{
public:

	struct float3 {
		float x, y, z;
	};

	float3 _circle[362];

	virtual void    render()
	{
		//! ָ�����µĲ������ͶӰ����
		glMatrixMode(GL_PROJECTION);
		//! ��ͶӰ��֤��ճɵ�λ����
		glLoadIdentity();
		glOrtho(0, _width, _height, 0, -100, 100);

		float cx = 100;
		float cy = 100;
		float cz = 0;
		float r = 80;

		glColor3f(1, 1, 1);

		_circle[0].x = cx;
		_circle[0].y = cy;
		_circle[0].z = cz;

		for (int i = 1; i < 362; ++i) {
			_circle[i].x = (float)cos((double)i * M_PI / 180) * r + cx;
			_circle[i].y = (float)sin((double)i * M_PI / 180) * r + cy;
			_circle[i].z = cz;
		}
		glEnableClientState(GL_VERTEX_ARRAY);
		// ����������Ϊƫ������������ȡ��һ�����ݵ�λ�ã�0��ʾ3��GL_FLOAT��ƫ�ƣ����Ի���sizeof(float3)
		glVertexPointer(3, GL_FLOAT, 0, _circle);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 362);
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