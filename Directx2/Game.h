#pragma once
#include "D3DApplication.h"
#include "D3DMesh.h"

class Game : public D3DApplication
{
	public:
		Game(HINSTANCE hInstance, const unsigned long _IDSAppTittle, const unsigned long _IDCApp);
		~Game();

		/* Override */
		virtual LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		/* Loads all textures used in game.
			PARAMS : 
				filesArr - Paths to texture files
				texturesNum - Number of textures used (must match number of paths to texture files). 
		*/
		virtual HRESULT LoadTextures(WCHAR *filesArr[], unsigned short texturesNum);

		virtual HRESULT LoadMeshModels(WCHAR *filesArr[], unsigned short modelsNum);

	protected:
		/* Overrride */
		virtual void Render();
		IDirect3DTexture9 **gameTextures;
		vector<D3DMesh*> appMeshModels;
};

