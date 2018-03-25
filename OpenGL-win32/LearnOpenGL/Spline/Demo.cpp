
#include <windows.h>
#include <tchar.h>
#include <math.h>
#include "CELLMath.hpp"
#include <vector>

#include "OpenGLWindow.h"

using namespace CELL;

class   Demo :public OpenGLWindow
{
public:

	tspline<float> _spline;

	std::vector<float3> _array;

	Demo() {
		// 关键点
		_spline.addPoint(float3(10, 10, 0));
		_spline.addPoint(float3(20, 100, 0));
		_spline.addPoint(float3(100, 80, 0));
		_spline.addPoint(float3(200, 100, 0));
		_spline.addPoint(float3(300, 10, 0));
		_spline.addPoint(float3(400, 150, 0));

		// 插值
		for (float t = 0; t < 1.0f; t += 0.01f) {
			float3 pos = _spline.interpolate(t);
			_array.push_back(pos);
		}
	}

	virtual void    render()
	{
		//! 指定以下的操作针对投影矩阵
		glMatrixMode(GL_PROJECTION);
		//! 将投影举证清空成单位矩阵
		glLoadIdentity();
		glOrtho(0, _width, _height, 0, -100, 100);
		
		glEnableClientState(GL_VERTEX_ARRAY);
		// 第三个参数为偏移量，用来获取下一个数据的位置，0表示3个GL_FLOAT的偏移，可以换成sizeof(float3)
		glVertexPointer(3, GL_FLOAT, sizeof(float3), &_array[0]);
		glDrawArrays(GL_LINE_STRIP, 0, _array.size());
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