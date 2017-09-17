#include "stdafx.h"

/* Texture indices macros. */
const int TEXTURE_GRASS = 0;
const int TEXTURE_FLOOR = 1;
/* Number of textures and mesh models used in application. */
const int TEXTURES_NUM = 4;
const int MESH_MODELS_NUM = 1;
/* Paths to textures and mesh models. */
WCHAR *texturePaths[TEXTURES_NUM] = { L"..//Textures//desert.jpg",  L"..//Textures//boat.png",   L"..//Textures//piramid.jpg",  L"..//Textures//desert.jpg" };
WCHAR *meshPaths[MESH_MODELS_NUM] = { L"../Textures/polHouse1.x" };

D3DVertex0 rect[] = 
{
	{ -2.0f, -2.0f, 0.0f, 1.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(0, 255, 0, 0) , 1.0f, 1.0f },
	{ 2.0f, -2.0f, 0.0f, 1.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(0, 255, 0, 0), 0.0f, 1.0f },
	{ -2.0f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(0, 255, 0, 0), 1.0f, 0.0f },
	{ 2.0f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(0, 255, 0, 0), 0.0f, 0.0f }
};

D3DVertex1 rect2[] =
{
	{ -2.0f, -2.0f, 0.0f, 1.0f, 1.0f },
	{ 2.0f, -2.0f, 0.0f, 0.0f, 1.0f },
	{ -2.0f, 2.0f, 0.0f, 1.0f, 0.0f },
	{ 2.0f, 2.0f, 0.0f, 0.0f, 0.0f }
};


V_XYZ_DIFFUSE cubeVertices[] = 
{
	{ -1.0f, 1.0f, -3.0f, D3DCOLOR_XRGB(0, 0, 255) },
    { 1.0f, 1.0f, -3.0f, D3DCOLOR_XRGB(0, 255, 0) },
    { -1.0f, -1.0f, -3.0f, D3DCOLOR_XRGB(255, 0, 0) },
    { 1.0f, -1.0f, -3.0f, D3DCOLOR_XRGB(0, 255, 255) },
    { -1.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255) },
    { 1.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0) },
    { -1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0) },
    { 1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 255) }
};

V_XYZ_DIFFUSE rectVertices3[] = 
{
	{ -2.0f, -2.0f, -3.0f,  D3DCOLOR_XRGB(0, 0, 255) },
    { 2.0f, -2.0f, -3.0f,  D3DCOLOR_XRGB(0, 255, 0) },
    { -2.0f, 2.0f, -3.0f,  D3DCOLOR_XRGB(0, 255, 255) },
	{ 2.0f, 2.0f, -3.0f,  D3DCOLOR_XRGB(255, 0, 0) }
};

V_XYZ_DIFFUSE triangleVertices1[] = 
{
	{ -3.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(0, 0, 255) },
    { 3.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 0) },
    { 0.0f, 3.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 255) }
};

V_XYZ_DIFFUSE rectVertices4[] = 
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

D3DVertex1 verticesCubeTexture[] =
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

D3DVertex3 rectFenceR[] =
{
	{ -1000.0f, -3.0f, 20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f },
	{ 1000.0f, -3.0f, 20.0f, 0.0f, 1.0f, 0.0f, 200.0f, 0.0f },
	{ 1000.0f, -3.0f, -5380.0f, 0.0f, 1.0f, 0.0f, 200.0f, 200.0f },
	{ -1000.0f, -3.0f, -5380.0f, 0.0f, 1.0f, 0.0f, 0.0f, 200.0f }
};

V_XYZ_TEX rectFenceL[] =
{
	{ 10.0f, -3.0f, 20.0f, 100.0f, 500.0f },
	{ 1000.0f, -3.0f, 20.0f, 0.0f, 500.0f },
	{ 10.0f, -3.0f, -5380.0f, 100.0f, 0.0f },
	{ 1000.0f, -3.0f, -5380.0f, 0.0f, 0.0f },
};