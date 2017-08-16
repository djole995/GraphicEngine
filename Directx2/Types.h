
#include "stdafx.h"

const int DEFAULT_SCREEN_WIDTH = 1366;
const int DEFAULT_SCREEN_HEIGHT = 768;

enum Direction { LEFT, RIGHT, UP, DOWN };

enum ObjectType { TRIANGLE, RECTANGLE, CIRCLE, CUBOID, PIRAMID };

struct V_XYZ
{
	float x, y, z;
};

struct V_XYZ_TEX : public V_XYZ
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

};

struct V_XYZ_COL
{
	float x, y, z;
	D3DCOLOR color;
};

struct V_XYZ_N_COL: public V_XYZ
{
	D3DVECTOR normal;
	D3DCOLOR color;
};

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


typedef struct Position
{
	float x, y, z;
	Direction direction;

	Position(float _x, float _y, float _z, Direction _direction)
	{
		x = _x;
		y = _y;
		z = _z;
		direction = _direction;
	}
} Position;


struct MatrixBufferType
{
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
};


