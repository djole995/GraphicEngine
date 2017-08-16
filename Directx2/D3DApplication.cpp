
#include "StdAfx.h"
#include "D3DApplication.h"

float rotate1 = 0.0f;


D3DApplication::D3DApplication(HINSTANCE hInstance, const unsigned long _IDSAppTittle, const unsigned long _IDCApp): ApplicationMain(hInstance, _IDSAppTittle, _IDCApp) 
{
	d3dI = Direct3DCreate9(D3D_SDK_VERSION);
}

D3DApplication::~D3DApplication(void)
{
}

HRESULT D3DApplication::InitGraphics(D3DPRESENT_PARAMETERS *d3dParams)
{
	HRESULT ret;
	if(d3dParams == NULL)
	{
		D3DPRESENT_PARAMETERS dp;
	
		ZeroMemory(&dp, sizeof(dp));

		dp.Windowed = true;
		dp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		dp.BackBufferFormat = D3DFMT_A8R8G8B8;
		dp.BackBufferWidth = DEFAULT_SCREEN_WIDTH;
		dp.BackBufferHeight = DEFAULT_SCREEN_HEIGHT;
		dp.BackBufferCount   = 1;
		dp.EnableAutoDepthStencil = true;
		dp.AutoDepthStencilFormat = D3DFMT_D16;

		ret = d3dI->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hAppMainWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &dp, &d3dDev);
	}
	else
	{
		ret = d3dI->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hAppMainWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, d3dParams, &d3dDev);
	}

	d3dDev->SetRenderState(D3DRS_ZENABLE, true);
	d3dDev->SetRenderState(D3DRS_LIGHTING, false);
	
	return ret;
}

HRESULT D3DApplication::InitBuffers(int _vertexBufferSize, DWORD _vertexBufferType, int _indexBufferSize)
{
	HRESULT ret;

	vertexBufferType = _vertexBufferType;
	vertexBufferSize = _vertexBufferSize;
	indexBufferSize = _indexBufferSize;
	ret = d3dDev->CreateVertexBuffer(vertexBufferSize, 0, vertexBufferType, D3DPOOL_MANAGED, &vertexBuffer, NULL);
	vertexBufferWriteLocation = 0;
	
	ret = d3dDev->CreateIndexBuffer(indexBufferSize*sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, NULL);
	indexBufferWriteIndex = 0;

	switch (vertexBufferType)
	{
	case D3DFVF_XYZ | D3DFVF_DIFFUSE:
		verticesSize = sizeof(V_XYZ_COL);
		break;
	case D3DFVF_XYZ | D3DFVF_TEX1:
		verticesSize = sizeof(V_XYZ_TEX);
	}
	

	return ret;
}

void D3DApplication::Render()
{

	d3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 255), 1.0f, 0);
	d3dDev->Clear(0, 0, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	
	d3dDev->BeginScene();

	d3dDev->SetFVF(vertexBufferType);

	d3dDev->SetStreamSource(0, vertexBuffer, 0, verticesSize);
	d3dDev->SetIndices(indexBuffer);

	D3DXMatrixLookAtLH(&matView,
					&D3DXVECTOR3 (0.0f, 0.0f, 20.0f),    // the camera position
					&D3DXVECTOR3 (0.0f, 0.0f, 0.0f),    // the look-at position
					&D3DXVECTOR3 (0.0f, 1.0f, 0.0f));    // the up direction

	d3dDev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

	D3DXMatrixPerspectiveFovLH(&matProjection,
									   D3DXToRadian(60),    // the horizontal field of view
									   1300.0f / 700.0f, // aspect ratio
									   1.0f,    // the near view-plane
									   5000.0f);    // the far view-planes

	d3dDev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection



	int vertexPosition = 0;

	for(unsigned int i = 0; i < appObjects.size(); i++)
	{
		
		d3dDev->SetTransform(D3DTS_WORLD, &(appObjects[i]->matScale 
			* appObjects[i]->matRotateX * appObjects[i]->matRotateY * appObjects[i]->matRotateZ
			* appObjects[i]->matTranslate));
		d3dDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, vertexPosition, 0, appObjects[i]->verticesNumber, 0, appObjects[i]->trianglesNumber);
		vertexPosition += appObjects[i]->verticesNumber;
	}

	d3dDev->EndScene();
	d3dDev->Present(0, 0, 0, 0);
}

LRESULT CALLBACK D3DApplication::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return ApplicationMain::MsgProc(hWnd, message, wParam, lParam);
}

void D3DApplication::FillBuffers(vector<WorldObject*> &_appObjects)
{
	appObjects = _appObjects;

	void *tmp;

	short indices[] =
	{
		0, 1, 2,
		2, 1, 3
	};

	short indices2[] =
	{
		0, 1, 2
	};

	/*short indicesCuboid[] =
	{
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 0, 6,    // side 2
		6, 0, 2,
		7, 5, 6,    // side 3
		6, 5, 4,
		3, 1, 7,    // side 4
		7, 1, 5,
		4, 5, 0,    // side 5
		0, 5, 1,
		3, 7, 2,    // side 6
		2, 7, 6,
	};*/

	short indicesCuboid[] =
	{
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 5, 6,    // side 2
		6, 5, 7,
		8, 9, 10,    // side 3
		10, 9, 11,
		12, 13, 14,    // side 4
		14, 13, 15,
		16, 17, 18,    // side 5
		18, 17, 19,
		20, 21, 22,    // side 6
		22, 21, 23,
	};

	for(unsigned int i = 0; i < appObjects.size(); i++)
	{
		appObjects[i]->indexBufferPosition = indexBufferWriteIndex;

		vertexBuffer->Lock(vertexBufferWriteLocation, 0, (void**)&tmp, 0);
		memcpy(tmp, appObjects[i]->vertices, appObjects[i]->verticesNumber * verticesSize);
		vertexBuffer->Unlock();
		
		vertexBufferWriteLocation = (vertexBufferWriteLocation >= vertexBufferSize) ? 0 
				: vertexBufferWriteLocation + appObjects[i]->verticesNumber * verticesSize;

		switch(appObjects[i]->objectType)
		{
		case TRIANGLE:
			indexBuffer->Lock(indexBufferWriteIndex, 0, (void**)&tmp, 0);
			memcpy(tmp, indices2, sizeof(indices2));
			indexBuffer->Unlock();

			appObjects[i]->trianglesNumber = 1;
			indexBufferWriteIndex = (indexBufferWriteIndex >= indexBufferSize) ? 0 : indexBufferWriteIndex + sizeof(indices2);
			
			break;
		case RECTANGLE:
			indexBuffer->Lock(indexBufferWriteIndex, 0, (void**)&tmp, 0);
			memcpy(tmp, indices, sizeof(indices));
			indexBuffer->Unlock();

			appObjects[i]->trianglesNumber = 2;
			indexBufferWriteIndex = (indexBufferWriteIndex >= indexBufferSize*sizeof(short)) ? 0 : indexBufferWriteIndex + sizeof(indices);

			break;
		case CUBOID:
			indexBuffer->Lock(indexBufferWriteIndex, 0, (void**)&tmp, 0);
			memcpy(tmp, indicesCuboid, sizeof(indicesCuboid));
			indexBuffer->Unlock();

			appObjects[i]->trianglesNumber = 12;
			indexBufferWriteIndex = (indexBufferWriteIndex >= indexBufferSize*sizeof(short)) ? 0 : indexBufferWriteIndex + sizeof(indicesCuboid);

			break;
		}
	}

}
