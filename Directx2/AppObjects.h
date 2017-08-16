#include "stdafx.h"

/* Texture indices macros. */
const int TEXTURE_GRASS = 0;
const int TEXTURE_FLOOR = 1;
/* Number of textures used in application. */
const int TEXTURES_NUM = 4;
/* Paths to textures. */
WCHAR *texturePaths[TEXTURES_NUM] = { L"D://Textures//grasstext.jpg",  L"D://Textures//floor.jpg",   L"D://Textures//piramid.jpg",  L"D://Textures//desert.jpg" };

V_XYZ_COL cubeVertices[] = 
{
	{ -3.0f, 3.0f, -5.0f, D3DCOLOR_XRGB(0, 0, 255) },
    { 3.0f, 3.0f, -5.0f, D3DCOLOR_XRGB(0, 255, 0) },
    { -3.0f, -3.0f, -5.0f, D3DCOLOR_XRGB(255, 0, 0) },
    { 3.0f, -3.0f, -5.0f, D3DCOLOR_XRGB(0, 255, 255) },
    { -3.0f, 3.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255) },
    { 3.0f, 3.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0) },
    { -3.0f, -3.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0) },
    { 3.0f, -3.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 255) }
};

V_XYZ_RHW_COL rectVertices[] = 
{
	{ 600.0f, 200.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255) },
    { 800.0f, 200.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0) },
    { 600.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 255) },
	{ 800.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0) }
};

V_XYZ_RHW_COL triangleVertices[] = 
{
	{ 600.0f, 500.0f, 100.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255) },
    { 800.0f, 500.0f, 100.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0) },
    { 600.0f, 700.0f, 100.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 255) }
};

V_XYZ_RHW_COL rectVertices2[] = 
{
	{ 200.0f, 100.0f, 1000.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 255) },
    { 400.0f, 100.0f, 1000.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 255) },
    { 200.0f, 200.0f, 1000.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255) },
	{ 400.0f, 200.0f, 1000.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0) }
};

V_XYZ_COL rectVertices3[] = 
{
	{ -2.0f, -2.0f, -3.0f,  D3DCOLOR_XRGB(0, 0, 255) },
    { 2.0f, -2.0f, -3.0f,  D3DCOLOR_XRGB(0, 255, 0) },
    { -2.0f, 2.0f, -3.0f,  D3DCOLOR_XRGB(0, 255, 255) },
	{ 2.0f, 2.0f, -3.0f,  D3DCOLOR_XRGB(255, 0, 0) }
};

V_XYZ_COL triangleVertices1[] = 
{
	{ -3.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(0, 0, 255) },
    { 3.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 0) },
    { 0.0f, 3.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 255) }
};

V_XYZ_COL rectVertices4[] = 
{
	{ -2.0f, -2.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 255) },
    { 2.0f, -2.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 255) },
    { -2.0f, 2.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255) },
	{ 2.0f, 2.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0) }
};

V_XYZ_TEX rectTexture[] =
{
	{ -2.0f, -2.0f, 0.0f, 1.0f, 1.0f },
	{ 2.0f, -2.0f, 0.0f, 0.0f, 1.0f },
	{ -2.0f, 2.0f, 0.0f, 1.0f, 0.0f },
	{ 2.0f, 2.0f, 0.0f, 0.0f, 0.0f }
};

V_XYZ_TEX verticesCubeTexture[] =
{
	{ -3.0f, -3.0f, 3.0f, 0.0f, 0.0f },    // side 1
	{ 3.0f, -3.0f, 3.0f, 0.0f, 2.0f },
	{ -3.0f, 3.0f, 3.0f, 2.0f, 0.0f },
	{ 3.0f, 3.0f, 3.0f, 2.0f, 2.0f },

	{ -3.0f, -3.0f, -3.0f, 0.0f, 0.0f },    // side 2
	{ -3.0f, 3.0f, -3.0f, 0.0f, 2.0f },
	{ 3.0f, -3.0f, -3.0f, 2.0f, 0.0f },
	{ 3.0f, 3.0f, -3.0f, 2.0f, 2.0f },

	{ -3.0f, 3.0f, -3.0f, 0.0f, 0.0f },    // side 3
	{ -3.0f, 3.0f, 3.0f, 0.0f, 2.0f },
	{ 3.0f, 3.0f, -3.0f, 2.0f, 0.0f },
	{ 3.0f, 3.0f, 3.0f, 2.0f, 2.0f },

	{ -3.0f, -3.0f, -3.0f,  0.0f, 0.0f },    // side 4
	{ 3.0f, -3.0f, -3.0f, 0.0f, 2.0f },
	{ -3.0f, -3.0f, 3.0f, 2.0f, 0.0f },
	{ 3.0f, -3.0f, 3.0f,  2.0f, 2.0f },

	{ 3.0f, -3.0f, -3.0f,  0.0f, 0.0f },    // side 5
	{ 3.0f, 3.0f, -3.0f,  0.0f, 2.0f },
	{ 3.0f, -3.0f, 3.0f,  2.0f, 0.0f },
	{ 3.0f, 3.0f, 3.0f,  2.0f, 2.0f },

	{ -3.0f, -3.0f, -3.0f,  0.0f, 0.0f },    // side 6
	{ -3.0f, -3.0f, 3.0f,  0.0f, 2.0f },
	{ -3.0f, 3.0f, -3.0f, 2.0f, 0.0f },
	{ -3.0f, 3.0f, 3.0f,  2.0f, 2.0f },
};

V_XYZ_TEX verticesCubeTexture2[] =
{
	{ -3.0f, -3.0f, 3.0f, 0.0f, 0.0f },    // side 1
	{ 3.0f, -3.0f, 3.0f, 0.0f, 1.0f },
	{ -3.0f, 3.0f, 3.0f, 1.0f, 0.0f },
	{ 3.0f, 3.0f, 3.0f, 1.0f, 1.0f },

	{ -3.0f, -3.0f, 0.0f, 0.0f, 0.0f },    // side 2
	{ -3.0f, 3.0f, 0.0f, 0.0f, 1.0f },
	{ 3.0f, -3.0f, 0.0f, 1.0f, 0.0f },
	{ 3.0f, 3.0f, 0.0f, 1.0f, 1.0f },

	{ -3.0f, 3.0f, 0.0f, 0.0f, 0.0f },    // side 3
	{ -3.0f, 3.0f, 3.0f, 0.0f, 1.0f },
	{ 3.0f, 3.0f, 0.0f, 1.0f, 0.0f },
	{ 3.0f, 3.0f, 3.0f, 1.0f, 1.0f },

	{ -3.0f, -3.0f, 0.0f,  0.0f, 0.0f },    // side 4
	{ 3.0f, -3.0f, 0.0f, 0.0f, 1.0f },
	{ -3.0f, -3.0f, 3.0f, 1.0f, 0.0f },
	{ 3.0f, -3.0f, 3.0f,  1.0f, 1.0f },

	{ 3.0f, -3.0f, 0.0f,  0.0f, 0.0f },    // side 5
	{ 3.0f, 3.0f, 0.0f,  0.0f, 1.0f },
	{ 3.0f, -3.0f, 3.0f,  1.0f, 0.0f },
	{ 3.0f, 3.0f, 3.0f,  1.0f, 1.0f },

	{ -3.0f, -3.0f, 0.0f,  0.0f, 0.0f },    // side 6
	{ -3.0f, -3.0f, 3.0f,  0.0f, 1.0f },
	{ -3.0f, 3.0f, 0.0f, 1.0f, 0.0f },
	{ -3.0f, 3.0f, 3.0f,  1.0f, 1.0f },
};



V_XYZ_TEX rectFenceR2[] =
{
	{ -1000.0f, -3.0f, 20.0f, 0.0f, 0.0f },
	{ 1000.0f, -3.0f, 20.0f, 100.0f, 0.0f },
	{ 1000.0f, -3.0f, -5380.0f, 100.0f, 500.0f },
	{ -1000.0f, -3.0f, -5380.0f, 0.0f, 500.0f },
};

V_XYZ_TEX rectFenceR[] =
{
	{ -1000.0f, -3.0f, 20.0f, 0.0f, 0.0f },
	{ 1000.0f, -3.0f, 20.0f, 200.0f, 0.0f },
	{ 1000.0f, -3.0f, -5380.0f, 200.0f, 200.0f },
	{ -1000.0f, -3.0f, -5380.0f, 0.0f, 200.0f },
};

V_XYZ_TEX rectFenceL[] =
{
	{ 10.0f, -3.0f, 20.0f, 100.0f, 500.0f },
	{ 1000.0f, -3.0f, 20.0f, 0.0f, 500.0f },
	{ 10.0f, -3.0f, -5380.0f, 100.0f, 0.0f },
	{ 1000.0f, -3.0f, -5380.0f, 0.0f, 0.0f },
};