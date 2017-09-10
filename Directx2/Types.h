
#include "stdafx.h"

const int DEFAULT_SCREEN_WIDTH = 1366;
const int DEFAULT_SCREEN_HEIGHT = 768;

enum Direction { LEFT, RIGHT, UP, DOWN };

enum ObjectType { TRIANGLE, RECTANGLE, CIRCLE, CUBOID, PIRAMID };

/* Supported vertex format constants. */
const DWORD D3DFVF_VERTEX0 = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;
const DWORD D3DFVF_VERTEX1 = D3DFVF_XYZ | D3DFVF_TEX1;
const DWORD D3DFVF_VERTEX2 = D3DFVF_XYZ | D3DFVF_DIFFUSE;
const DWORD D3DFVF_VERTEX3 = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;



struct V_XYZ
{
	float x, y, z;
};

typedef struct V_XYZ_TEX : public V_XYZ
{
	float u, v;

	V_XYZ_TEX(float _x, float _y, float _z, float _u, float _v)
	{
		x = _x;
		y = _y;
		z = _z;
		u = _u;
		v = _v;
	}

} V_XYZ_TEX, D3DVertex1;

typedef struct V_XYZN_TEX : public V_XYZ
{
	float nx, ny, nz;
	float u, v;

	V_XYZN_TEX(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u, float _v)
	{
		x = _x;
		y = _y;
		z = _z;
		nx = _nx;
		ny = _ny;
		nz = _nz;
		u = _u;
		v = _v;
	}

} V_XYZN_TEX, D3DVertex3;

typedef struct V_XYZ_DIFFUSE : public V_XYZ
{
	D3DCOLOR diffuse;

	V_XYZ_DIFFUSE(float _x, float _y, float _z, D3DCOLOR _diffuse)
	{
		x = _x;
		y = _y;
		z = _z;
		diffuse = _diffuse;
	}
} V_XYZ_DIFFUSE, D3DVertex2;

typedef struct V_XYZN_DIFFUSE_TEX: public V_XYZ
{
	float nx, ny, nz;
	D3DCOLOR diffuse;
	float u, v;

	V_XYZN_DIFFUSE_TEX(float _x, float _y, float _z, float _nx, float _ny, float _nz, D3DCOLOR _diffuse, float _u, float _v)
	{
		x = _x;
		y = _y;
		z = _z;
		nx = _nx;
		ny = _ny;
		nz = _nz;
		diffuse = _diffuse;
		u = _u;
		v = _v;
	}
} V_XYZN_DIFFUSE_TEX, D3DVertex0;

struct V_XYZ_TEX_COL : public V_XYZ
{
	float tu, tv;
	D3DCOLOR color;
};

struct V_XYZ_RHW_COL
{
	float x, y, z;
	float rhw;
	D3DCOLOR color;
};

typedef struct WorldObject
{
	V_XYZ *vertices;
	ObjectType objectType;
	D3DXMATRIX matTranslate, matRotateX, matRotateY, matRotateZ, matScale;
	int indexBufferPosition;
	short verticesNumber;
	short trianglesNumber;
	int textureIndex;

	WorldObject(V_XYZ *_vertices, ObjectType _objectType, V_XYZ translate, V_XYZ rotate, V_XYZ scale, short _verticesNumber, int _textureIndex)
	{
		vertices = _vertices;
		objectType = _objectType;
		verticesNumber = _verticesNumber;
		D3DXMatrixTranslation(&matTranslate, translate.x, translate.y, translate.z);
		D3DXMatrixRotationX(&matRotateX, rotate.x);
		D3DXMatrixRotationY(&matRotateY, rotate.y);
		D3DXMatrixRotationZ(&matRotateZ, rotate.z);
		D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
		indexBufferPosition = -1;
		textureIndex = _textureIndex;
	}

} WorldObject;


/* Vertex Buffer struct.
   Members:
	data - actual vertex buffer data
	type - vertex buffer type (FVF)
	size - buffer size (in bytes)
	tail - current write location (offset in bytes)
	verticesSize - Size of single vertex in buffer 
*/
struct VertexBuffer
{
	IDirect3DVertexBuffer9 *data;
	DWORD type;
	unsigned int size;
	unsigned int tail;
	unsigned int verticesSize;
};


struct MatrixBufferType
{
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
};


