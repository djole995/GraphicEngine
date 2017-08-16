
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

HRESULT D3DApplication::InitBuffers(int _vertexBufferSize[], DWORD _vertexBufferType[], 
									unsigned short vertexBuffersNum, int _indexBufferSize)
{
	HRESULT ret;

	/*vertexBufferType = _vertexBufferType;
	vertexBufferSize = _vertexBufferSize;*/
	indexBufferSize = _indexBufferSize;
	ret = d3dDev->CreateIndexBuffer(indexBufferSize * sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, NULL);
	indexBufferWriteIndex = 0;

	for (unsigned int i = 0; i < vertexBuffersNum; i++)
	{
		vertexBuffers.push_back(VertexBuffer());

		vertexBuffers[i].size = _vertexBufferSize[i];
		vertexBuffers[i].type = _vertexBufferType[i];

		ret = d3dDev->CreateVertexBuffer(_vertexBufferSize[i], 0, _vertexBufferType[i], D3DPOOL_MANAGED, &vertexBuffers[i].data, NULL);
		vertexBuffers[i].tail = 0;

		switch (_vertexBufferType[i])
		{
			case D3DFVF_XYZ | D3DFVF_DIFFUSE:
				vertexBuffers[i].verticesSize = sizeof(V_XYZ_DIFFUSE);
				break;
			case D3DFVF_XYZ | D3DFVF_TEX1:
				vertexBuffers[i].verticesSize = sizeof(V_XYZ_TEX);
				break;
			case D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1:
				vertexBuffers[i].verticesSize = sizeof(V_XYZN_DIFFUSE_TEX);
		}

	}
	return ret;
}

void D3DApplication::Render()
{

	d3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 255), 1.0f, 0);
	d3dDev->Clear(0, 0, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	
	d3dDev->BeginScene();

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

	for(unsigned int i = 0; i < appObjects.size(); i++)
	{
		int vertexPosition = 0;
		d3dDev->SetFVF(vertexBuffers[i].type);

		d3dDev->SetStreamSource(0, vertexBuffers[i].data, 0, vertexBuffers[i].verticesSize);

		for (unsigned int j = 0; j < appObjects[i].size(); j++)
		{
			d3dDev->SetTransform(D3DTS_WORLD, &(appObjects[i][j]->matScale
				* appObjects[i][j]->matRotateX * appObjects[i][j]->matRotateY * appObjects[i][j]->matRotateZ
				* appObjects[i][j]->matTranslate));
			d3dDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, vertexPosition, 0, appObjects[i][j]->verticesNumber, 0, appObjects[i][j]->trianglesNumber);
			vertexPosition += appObjects[i][j]->verticesNumber;
		}
	}

	d3dDev->EndScene();
	d3dDev->Present(0, 0, 0, 0);
}

LRESULT CALLBACK D3DApplication::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return ApplicationMain::MsgProc(hWnd, message, wParam, lParam);
}

void D3DApplication::FillBuffers(vector<vector<WorldObject*>> &_appObjects)
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
		for (unsigned int j = 0; j < appObjects[i].size(); j++)
		{
			appObjects[i][j]->indexBufferPosition = indexBufferWriteIndex;

			vertexBuffers[i].data->Lock(vertexBuffers[i].tail, 0, (void**)&tmp, 0);
			memcpy(tmp, appObjects[i][j]->vertices, appObjects[i][j]->verticesNumber * vertexBuffers[i].verticesSize);
			vertexBuffers[i].data->Unlock();

			vertexBuffers[i].tail = (vertexBuffers[i].tail >= vertexBuffers[i].size) ? 0
				: vertexBuffers[i].tail + appObjects[i][j]->verticesNumber * vertexBuffers[i].verticesSize;

			switch (appObjects[i][j]->objectType)
			{
			case TRIANGLE:
				indexBuffer->Lock(indexBufferWriteIndex, 0, (void**)&tmp, 0);
				memcpy(tmp, indices2, sizeof(indices2));
				indexBuffer->Unlock();

				appObjects[i][j]->trianglesNumber = 1;
				indexBufferWriteIndex = (indexBufferWriteIndex >= indexBufferSize) ? 0 : indexBufferWriteIndex + sizeof(indices2);

				break;
			case RECTANGLE:
				indexBuffer->Lock(indexBufferWriteIndex, 0, (void**)&tmp, 0);
				memcpy(tmp, indices, sizeof(indices));
				indexBuffer->Unlock();

				appObjects[i][j]->trianglesNumber = 2;
				indexBufferWriteIndex = (indexBufferWriteIndex >= indexBufferSize * sizeof(short)) ? 0 : indexBufferWriteIndex + sizeof(indices);

				break;
			case CUBOID:
				indexBuffer->Lock(indexBufferWriteIndex, 0, (void**)&tmp, 0);
				memcpy(tmp, indicesCuboid, sizeof(indicesCuboid));
				indexBuffer->Unlock();

				appObjects[i][j]->trianglesNumber = 12;
				indexBufferWriteIndex = (indexBufferWriteIndex >= indexBufferSize * sizeof(short)) ? 0 : indexBufferWriteIndex + sizeof(indicesCuboid);

				break;
			}
		}
	}

}
