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

	int vBuffSize[] = { sizeof(D3DVertex3) * 100, sizeof(D3DVertex1) * 100, sizeof(D3DVertex0) * 100 };
	DWORD vBuffType[] = { D3DFVF_VERTEX3, D3DFVF_VERTEX1,  D3DFVF_VERTEX0 };

	if (FAILED(application->InitBuffers(vBuffSize, vBuffType, 3, 300)))
	{
		MessageBox(NULL, L"Initializing D3D Buffers failed.", NULL, MB_OK);
	}

	if (FAILED(application->LoadTextures(texturePaths, TEXTURES_NUM)))
	{
		MessageBox(NULL, L"Loading textures failed.", NULL, MB_OK);
	}

	// Translate, scale and rotate parameters for objects init. 
	V_XYZ t = {0, -1, 0};
	V_XYZ s = {1, 1, 1}; 
	V_XYZ r = {0, 0, 0};
	vector<vector<WorldObject*>> worldObjects(3, vector<WorldObject*>());
	
	t = { 0, -1, 200 };
	s = { 1, 1, 1 };
	r = { 0, 0, 0 };
	// Insert terain
	worldObjects[0].push_back(new WorldObject(rectFenceR, RECTANGLE, t, r, s, 4, 0));

	application->LoadVertexShader(L"../Shaders/VertexShader.hlsl", "main");
	application->LoadPixelShader(L"../Shaders/PixelShader.hlsl", "main");

	application->FillBuffers(worldObjects);

	if (FAILED(application->LoadMeshModel(meshPaths[1], stoneTexturePath, -20, 70, -250)))
	{
		MessageBox(NULL, L"Loading mesh models failed.", L"Error", MB_OK);
		return -1;
	}

	if (FAILED(application->LoadMeshModel(meshPaths[0], houseTexturePath, 0, -4, -100)))
	{
		MessageBox(NULL, L"Loading mesh models failed.", L"Error", MB_OK);
		return -1;
	}

	/*if (FAILED(application->LoadMeshModel(meshPaths[2], weedTexturePath, 0, 0, 0)))
	{
		MessageBox(NULL, L"Loading mesh models failed.", L"Error", MB_OK);
		return -1;
	}*/

	appRetValue = application->Run();


	delete application;

	return 0;
}