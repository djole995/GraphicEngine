#include "stdafx.h"
#include "Game.h"

float zZoom = 0;
int currentCursorXPosition = DEFAULT_SCREEN_WIDTH / 2;
int newCursorXPosition = 0;
float cameraLookAtX = 0;
float cameraLookAtY = 0;
int currentCursorYPosition = DEFAULT_SCREEN_HEIGHT / 2 - 42;
int newCursorYPosition = 0;
float cameraXPos = 0;
float cameraYPos = 0;


Game::Game(HINSTANCE hInstance, const unsigned long _IDSAppTittle, const unsigned long _IDCApp): 
	D3DApplication(hInstance, _IDSAppTittle, _IDCApp)
{
}


Game::~Game()
{

}

LRESULT Game::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		D3DApplication::MsgProc(hWnd, message, wParam, lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			zZoom -= 1;
			break;
		case VK_DOWN:
			zZoom += 1;
			break;
		case VK_LEFT:
			cameraXPos += 0.5f;
			break;
		case VK_RIGHT:
			cameraXPos -= 0.5f;
			cameraLookAtY += 0.5f;
			break;
		case VK_SPACE:
			cameraYPos += 2.0f;
			break;
		case VK_SHIFT:
			if(cameraYPos > 0.0f)
				cameraYPos -= 2.0f;
			break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}

		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_SPACE:
			/*Sleep(500);
			cameraLookAtY -= 0.5f;
			cameraYPos = 0.0f;*/
			break;
		}
		break;
	case WM_MOUSEMOVE:
		newCursorXPosition = LOWORD(lParam);
		if (abs(currentCursorXPosition - newCursorXPosition) >= 1)
		{
			if (currentCursorXPosition > newCursorXPosition)
				cameraLookAtX += 1.0f;
			else
				cameraLookAtX -= 1.0f;

			SetCursorPos(DEFAULT_SCREEN_WIDTH/2, currentCursorYPosition);
		}

		newCursorYPosition = HIWORD(lParam);
		if (abs(currentCursorYPosition - newCursorYPosition) >= 2)
		{
			if (currentCursorYPosition > newCursorYPosition)
				cameraLookAtY += 0.2f;
			else
				cameraLookAtY -= 0.2f;

			SetCursorPos(currentCursorXPosition, DEFAULT_SCREEN_HEIGHT / 2);
		}

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

HRESULT Game::LoadTextures(WCHAR *filesArr[], unsigned short texturesNum)
{
	gameTextures = new IDirect3DTexture9*[texturesNum];
	
	HRESULT ret = S_OK;
	for (unsigned int i = 0; i < texturesNum; i++)
	{
		ret = D3DXCreateTextureFromFile(d3dDev, filesArr[i], &gameTextures[i]);
		if (FAILED(ret))
			return ret;
	}
	return ret;
}

void Game::Render()
{
	static D3DCAPS9 caps;
	static int cnt = 0;

	static IDirect3DPixelShader9 *s;
	static IDirect3DVertexShader9 *v;
	static LPD3DXBUFFER buffS;
	static LPD3DXBUFFER buffV;
	static LPD3DXBUFFER pixelShader;
	static LPD3DXBUFFER vertexShader;
	//static ID3DXEffect *effect = NULL;

	if (cnt == 0)
	{
		D3DXCompileShaderFromFile(L"PixelShader.hlsl", NULL, NULL, "main", D3DXGetPixelShaderProfile(d3dDev), 0, &pixelShader,
			&buffS, NULL);
		D3DXCompileShaderFromFile(L"VertexShader.hlsl", NULL, NULL, "main", D3DXGetVertexShaderProfile(d3dDev), 0, &vertexShader,
			&buffV, NULL);

		d3dDev->GetPixelShader(&s);
		d3dDev->GetVertexShader(&v);
		d3dDev->CreatePixelShader((DWORD*)pixelShader->GetBufferPointer(), &s);
		d3dDev->CreateVertexShader((DWORD*)vertexShader->GetBufferPointer(), &v);
		//D3DXCreateEffectFromFileA(d3dDev, "Blinn.fx", 0, 0, 0, 0, &effect, 0);
		cnt = 1;
	}
	

	//d3dDev->SetVertexShader(v);
	//d3dDev->SetPixelShader(s);

	if (cnt == 1)
	{
		cnt = 2;
		if (FAILED(d3dDev->GetDeviceCaps(&caps)))
		{
			MessageBox(NULL, L"Failed to retrive device capabilities!", NULL, MB_OK);
		}
		else
		{
			d3dDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
			d3dDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
			d3dDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
			d3dDev->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, caps.MaxAnisotropy);
		}
	}

	d3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(90, 90, 255), 1.0f, 0);
	d3dDev->Clear(0, 0, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3dDev->BeginScene();


	d3dDev->SetIndices(indexBuffer);

	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(cameraXPos, cameraYPos, zZoom+20.0f),    // the camera position
		&D3DXVECTOR3(cameraLookAtX+cameraXPos, cameraLookAtY, zZoom+0.0f),    // the look-at position
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));    // the up direction

	d3dDev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(60),    // the horizontal field of view
		1300.0f / 700.0f, // aspect ratio
		1.0f,    // the near view-plane
		100.0f);    // the far view-planes

	d3dDev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection



	int vertexPosition = 0;

	/* Should uncomment (and modify if needed) when using models with alpha less than 1 
	to determine influence of both object itself and user defined alpha on resulting transparency.  */
	/*d3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	d3dDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3dDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);*/

	D3DXMatrixTranspose(&matView, &matView);
	D3DXMatrixTranspose(&matProjection, &matProjection);

	d3dDev->SetVertexShaderConstantF(4, matView, 4);
	d3dDev->SetVertexShaderConstantF(8, matProjection, 4);

	for (unsigned int i = 0; i < appObjects.size(); i++)
	{
		int vertexPosition = 0;
		d3dDev->SetFVF(vertexBuffers[i].type);

		d3dDev->SetStreamSource(0, vertexBuffers[i].data, 0, vertexBuffers[i].verticesSize);

		for (unsigned int j = 0; j < appObjects[i].size(); j++)
		{
			d3dDev->SetTexture(0, gameTextures[appObjects[i][j]->textureIndex]);
			if (j == 1 && i == 0)
			{
				static float rot = 0;
				/*appObjects[i]->matRotateX.m[0][0] -= 0.01f;
				appObjects[i]->matRotateX.m[1][0] -= 0.01f;
				appObjects[i]->matRotateX.m[2][0] -= 0.01f;*/
				D3DXMatrixRotationY(&appObjects[i][j]->matRotateY, rot);
				D3DXMatrixRotationX(&appObjects[i][j]->matRotateX, rot);
				D3DXMatrixRotationZ(&appObjects[i][j]->matRotateZ, rot);
				rot += 0.01f;
				/*For gun.*/
				/*D3DXMatrixRotationY(&(appObjects[i]->matRotateX), cameraLookAtX);
				D3DXMatrixTranslation(&(appObjects[i]->matTranslate), cameraLookAtX, 0, zZoom+18);*/
			}

			/* Only used with default graphic pipeline. Doesn't have any influence when using custom shaders. */
			d3dDev->SetTransform(D3DTS_WORLD, &(appObjects[i][j]->matScale
				* appObjects[i][j]->matRotateX * appObjects[i][j]->matRotateY * appObjects[i][j]->matRotateZ
				* appObjects[i][j]->matTranslate));

			
			/* Setting global variables for custom shaders. */
			D3DXMATRIX matWorld = appObjects[i][j]->matScale
				* appObjects[i][j]->matRotateX * appObjects[i][j]->matRotateY * appObjects[i][j]->matRotateZ
				* appObjects[i][j]->matTranslate;

			D3DXMatrixTranspose(&matWorld, &matWorld);

			d3dDev->SetVertexShaderConstantF(0, matWorld, 4);

			d3dDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, vertexPosition, 0, appObjects[i][j]->verticesNumber, appObjects[i][j]->indexBufferPosition, appObjects[i][j]->trianglesNumber);
			vertexPosition += appObjects[i][j]->verticesNumber;
		}
	}

	d3dDev->EndScene();
	d3dDev->Present(0, 0, 0, 0);
}



