
#include <windows.h>
#include <tchar.h>
#include <math.h>
#include "CELLMath.hpp"
#include "OpenGLWindow.h"
#include <vector>
#include<gl/glu.h>
using namespace CELL;

struct Vertex
{

	float x, y, z;
	float u, v;
};
class   SamplerTexture :public OpenGLWindow
{
	GLuint  _texture;
public:
	SamplerTexture()
	{
	}


	virtual void    onInitGL()
	{
		// 启用2D Texture
		glEnable(GL_TEXTURE_2D);
		// 根据纹理参数返回n个纹理索引,这里_texture记录纹理索引,没有分配现存
		glGenTextures(1, &_texture);
		// 允许建立一个绑定到目标纹理的有名称的纹理
		// 告诉opengl接下来对这个纹理做操作
		glBindTexture(GL_TEXTURE_2D, _texture);
		// 随机生成像素信息
		char*   data = new char[128 * 128 * 4];
		for (int i = 0; i < 128 * 128 * 4; ++i)
		{
			data[i] = rand() % 255;
		}
		/*
		GL_TEXTURE_MAG_FILTER和GL_TEXTURE_MIN_FILTER这两个参数指定纹理在映射到物体表面上时的缩放效果。
		GL_TEXTURE_MIN_FILTER是缩小情况；
		GL_TEXTURE_MAG_FILTER是放大情况。
		GL_LINEAR表示缩放的时候的插值方式为线性
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// 分配显存等
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 128, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	}
	virtual void    render()
	{
#define M_PI (3.14159265358979323846)
		//! 指定以下的操作针对投影矩阵
		glMatrixMode(GL_PROJECTION);
		//! 将投影举证清空成单位矩阵
		glLoadIdentity();

		gluPerspective(60, double(_width) / double(_height), 0.1, 1000);

		//uv左边范围为0到1
		Vertex cubeVertices[] =
		{
			{ -1.0f,-1.0f, 1.0f,   0,  0 },
			{ 1.0f,-1.0f, 1.0f,    0,  1 },
			{ 1.0f, 1.0f, 1.0f,    1,  1 },
			{ -1.0f, 1.0f, 1.0f,    1,  0 },
		};
		//! 
		glMatrixMode(GL_MODELVIEW);
		glBindTexture(GL_TEXTURE_2D, _texture);
#if 0
		glEnable(GL_DEPTH_TEST);
		glInterleavedArrays(GL_T2F_V3F, sizeof(Vertex), cubeVertices);
#else
		glEnable(GL_DEPTH_TEST);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &cubeVertices[0].x);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &cubeVertices[0].u);
#endif

		//! 清成单位矩阵
		glLoadIdentity();
		//! 产生一个矩阵
		glTranslatef(0, 0, -10);
		glDrawArrays(GL_QUADS, 0, 4);
	}
};

int __stdcall WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
)
{

	SamplerTexture    instance;
	instance.main(800, 600);


	return  0;
}