
#include <windows.h>
#include <tchar.h>
#include <math.h>
#include "CELLMath.hpp"
#include "OpenGLWindow.h"
#include <vector>
#include<gl/glu.h>
#include <iostream>
#include <string>
#include "FreeImage.h"

using namespace std;
using namespace CELL;

struct Vertex
{
	float u, v;
	float x, y, z;
};
class   SamplerTexture :public OpenGLWindow
{
	GLuint  _texture;
public:
	SamplerTexture()
	{
	}

	unsigned createTextureFromImage(const char* fileName) {
		FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileName, 0);
		if (fifmt == FIF_UNKNOWN) {
			return 0;
		}
		
		FIBITMAP *dib = FreeImage_Load(fifmt, fileName, 0);
		
		FREE_IMAGE_COLOR_TYPE type = FreeImage_GetColorType(dib);

		FIBITMAP* temp = dib;
		dib = FreeImage_ConvertTo32Bits(dib);
		FreeImage_Unload(temp);
		BYTE*   pixels = (BYTE*)FreeImage_GetBits(dib);
		int     width = FreeImage_GetWidth(dib);
		int     height = FreeImage_GetHeight(dib);

		for (int i = 0; i < width * height * 4; i += 4)
		{
			BYTE temp = pixels[i];
			pixels[i] = pixels[i + 2];
			pixels[i + 2] = temp;
		}

		unsigned    res = createTexture(width, height, pixels);
		FreeImage_Unload(dib);
		return      res;
	}

	unsigned    createTexture(int w, int h, const void* data)
	{
		unsigned    texId;
		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		return  texId;
	}

	virtual void    onInitGL()
	{
		_texture = createTextureFromImage("1.png");
	}

	virtual void    render()
	{
		//! 指定以下的操作针对投影矩阵
		glMatrixMode(GL_PROJECTION);
		//! 将投影举证清空成单位矩阵
		glLoadIdentity();

		gluPerspective(60, double(_width) / double(_height), 0.1, 1000);

		//uv左边范围为0到1
		Vertex cubeVertices[] =
		{
			{   0,  0, -1.0f,-1.0f, 1.0f},
			{	0,  1,  1.0f,-1.0f, 1.0f},
			{   1,  1, 1.0f, 1.0f, 1.0f},
			{	1,  0,  -1.0f, 1.0f, 1.0f},
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
		//uv 2维的， GL_FLOAT类型
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