// Directx2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Directx2.h"
#include "Game.h"
#include "AppObjects.h"

// Global Variables:
HINSTANCE hInst;								// current instance

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	int appRetValue;

	Game* application = new Game(hInstance, IDS_APP_TITLE, IDC_DIRECTX2);

	// Perform application initialization:
	if (!application->InitWindow(SW_MAXIMIZE))
	{
		MessageBox(NULL, L"Initializing window failed", NULL, MB_OK);
	}

	if (FAILED(application->InitGraphics(NULL)))
	{
		MessageBox(NULL, L"Initializing graphics failed.", NULL, MB_OK);
	}

	int vBuffSize[] = { sizeof(D3DVertex1) * 100, sizeof(D3DVertex1) * 100, sizeof(D3DVertex0) * 100 };
	DWORD vBuffType[] = { D3DFVF_XYZ | D3DFVF_TEX1, D3DFVF_XYZ | D3DFVF_TEX1,  D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 };

	if (FAILED(application->InitBuffers(vBuffSize, vBuffType, 3, 300)))
	{
		MessageBox(NULL, L"Initializing D3D Buffers failed.", NULL, MB_OK);
	}

	if (FAILED(application->LoadTextures(texturePaths, TEXTURES_NUM)))
	{
		MessageBox(NULL, L"Loading textures failed.", NULL, MB_OK);
	}

	V_XYZ t = {0, -1, 0};
	V_XYZ s = {1, 1, 1}; 
	V_XYZ r = {0, 0, 0};
	vector<vector<WorldObject*>> worldObjects(3, vector<WorldObject*>());

	t = { 0, 0, 0 };
	s = { 1, 1, 1 };
	r = { 0, 0, 0 };

	//worldObjects.push_back(new WorldObject(verticesCubeTexture, CUBOID, t, r, s, 4));
	/*t.x = 5;
	worldObjects.push_back(new WorldObject(rectVertices4, RECTANGLE, t, r, s, 4));
	t.z = 10;
	worldObjects.push_back(new WorldObject(rectVertices4, RECTANGLE, t, r, s, 4));
	t.z = 0;
	t.x = 2;
	worldObjects.push_back(new WorldObject(rectVertices4, RECTANGLE, t, r, s, 4));
	t.y = -3;
	worldObjects.push_back(new WorldObject(triangleVertices1, TRIANGLE, t, r, s, 3));
	t.x = -10;
	t.z = 0;
	t.y = 0;
	worldObjects.push_back(new WorldObject(triangleVertices1, TRIANGLE, t, r, s, 3));*/
	//worldObjects[0].push_back(new WorldObject(cubeVertices, CUBOID, t, r, s, 4, 1));
	
	t = { 0, -1, 0 };
	s = { 1, 1, 1 };
	r = { 0, 0, 0 };
	worldObjects[0].push_back(new WorldObject(rectFenceR, RECTANGLE, t, r, s, 4, 0));
	//worldObjects.push_back(new WorldObject(rectTexture, RECTANGLE, t, r, s, 4, 0));
	t.z = 18;
	t.y = 0.2f;
	t.x = 0.1f;
	//worldObjects.push_back(new WorldObject(rectTexture, RECTANGLE, t, r, s, 4, 0));



	t = { 0, 0, 0 };
	s = { 1, 1, 1 };
	r = { 0, 0, 0 };

	worldObjects[0].push_back(new WorldObject(verticesCubeTexture, CUBOID, t, r, s, 24, 0));
	
	t.x = 8;
	t.y = 0;
	t.z = 0;
	worldObjects[0].push_back(new WorldObject(verticesCubeTexture, CUBOID, t, r, s, 24, 1));
	t.x = -8;
	worldObjects[2].push_back(new WorldObject(rect, RECTANGLE, t, r, s, 4, 1));


/*	t.x = 1;
	t.y = 1;
	t.z = -10;
	s.x = 0.5f;
	s.y = 0.5f;
	s.z = 0.5f;
	worldObjects.push_back(new WorldObject(cubeVertices, CUBOID, t, r, s, 8));*/

	application->FillBuffers(worldObjects);

	appRetValue = application->Run();

	return 0;
}