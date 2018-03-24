
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
	std::vector<float3> _keys;
	bool _isButtonDown;
	size_t _selectIndex;
	POINT _mouseOld;

	Demo() {
		_isButtonDown = false;
		_selectIndex = -1;
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

		for (int i = 0; i < _spline.getNumPoints(); ++i) {
			_keys.push_back(_spline.getPoint(i));
		}
	}

	virtual void    render()
	{
		//! 指定以下的操作针对投影矩阵
		glMatrixMode(GL_PROJECTION);
		//! 将投影举证清空成单位矩阵
		glLoadIdentity();
		glOrtho(0, _width, _height, 0, -100, 100);
		
		//glLineWidth(5);
		//glEnab le(GL_LINE_STIPPLE);
		//glLineStipple(1, 0x06cc);	//后一个为pattern

		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnableClientState(GL_VERTEX_ARRAY);
		// 第三个参数为偏移量，用来获取下一个数据的位置，0表示3个GL_FLOAT的偏移，可以换成sizeof(float3)
		glVertexPointer(3, GL_FLOAT, sizeof(float3), &_array[0]);
		glDrawArrays(GL_LINE_STRIP, 0, _array.size());
		
		glPointSize(8);
		glVertexPointer(3, GL_FLOAT, sizeof(float3), &_keys[0]);
		glDrawArrays(GL_POINTS, 0, _keys.size());
	}

	virtual LRESULT events(HWND hwnd, UINT msgId, WPARAM wParam, LPARAM lParam)
	{
		switch (msgId)
		{
		case WM_CLOSE:
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;
		case WM_LBUTTONDOWN: {
			_isButtonDown = true;
			_selectIndex = -1;
			POINT pt = { LOWORD(lParam), HIWORD(lParam) };
			_mouseOld = pt;

			for (size_t i = 0; i < _keys.size(); ++i) {
				RECT rt;
				rt.left = _keys[i].x - 4;
				rt.right = _keys[i].x + 4;
				rt.top = _keys[i].y - 4;
				rt.bottom = _keys[i].y + 4;

				if (PtInRect(&rt, pt)) {
					_selectIndex = i;
					break;
				}
			}
		}
			break;
		case WM_LBUTTONUP: {
			_isButtonDown = false;
			_selectIndex = -1;
		}
			break;
		case WM_MOUSEMOVE: {
			if (_isButtonDown && _selectIndex != -1) {
				POINT pt = { LOWORD(lParam), HIWORD(lParam) };
				POINT off = { pt.x - _mouseOld.x, pt.y - _mouseOld.y };
				_mouseOld = pt;
				_keys[_selectIndex].x += off.x;
				_keys[_selectIndex].y += off.y;

				_spline.getPoint(_selectIndex).x += off.x;
				_spline.getPoint(_selectIndex).y += off.y;
				_spline.recalcTangents();

				_array.clear();
				for (float t = 0; t < 1.0f; t += 0.01f) {
					float3 pos = _spline.interpolate(t);
					_array.push_back(pos);
				}
			}
		}
			break;
		default:
			return DefWindowProc(hwnd, msgId, wParam, lParam);
		}
		return  0;
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