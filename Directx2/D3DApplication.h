#pragma once
#include "applicationmain.h"

/* Base D3D Application class, should be inherited with render and vertex bufers fill methods overrided. */ 
class D3DApplication : public ApplicationMain
{
public:
	/* Creates only device interface d3dI. */
	D3DApplication(HINSTANCE hInstance, const unsigned long _IDSAppTittle, const unsigned long _IDCApp);
	~D3DApplication(void);

	/* Initiallize D3D device. if d3dParams is NULL default parameters are used. */
	virtual HRESULT InitGraphics(D3DPRESENT_PARAMETERS *d3dParams);
	/* Initiallize vertex and index buffers. Vertex buffer size is counted in bytes, index buffer size in number of elems. */
	virtual HRESULT InitBuffers(int _vertexBufferSize[], DWORD vertexBufferType[], 
		unsigned short vertexBuffersNum,  int indexBufferSize);
	/* Fill vertex buffer with WorldObject structure vertices and internally fill index buffers based on objectType param. 
	Supports triangles, rects and cuboids (Override to support more specific shapes of objects). */
	virtual void FillBuffers(vector<vector<WorldObject*>> &appObjects);

	/** @brief Loads and sets active pixel shader.
		
		@param sourceFileName path to shader source file
		@param entryPoint name of function which presents entry point of shader program (main function).

	*/
	virtual void LoadPixelShader(const WCHAR* sourceFileName, const char entryPoint[]);

	/** @brief Loads and sets active vertex shader.

	@param sourceFileName path to shader source file
	@param entryPoint name of function which presents entry point of shader program (main function).

	*/
	virtual void LoadVertexShader(const WCHAR* sourceFileName, const char entryPoint[]);

protected:
	/* Should be defined for every application. 
	This base realization only draw all objects without setting textures. (Override) */
	virtual void Render();
	/* Should be defined for every application. (Override) */
	virtual LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/* D3D Interface. */
	IDirect3D9 *d3dI;
	/* D3D device Interface. */
	IDirect3DDevice9 *d3dDev;
	/* Stores all vertices used in application. Filled in FillBuffers function. */
	vector<VertexBuffer> vertexBuffers;
	/* Stores all vertices used in application. Filled in FillBuffers function. */
	/* Stores drawing path indices for every object used in application. */
	IDirect3DIndexBuffer9 *indexBuffer;
	/* Current write location in index buffer(tail), Used in Fillbuffers function. */
	int indexBufferWriteIndex;
	int indexBufferSize;
	vector<vector<WorldObject*>> appObjects;
	D3DXMATRIX matProjection;
	D3DXMATRIX matView;

	/* Application vertex shader. If not set Direct3D is used. */
	IDirect3DVertexShader9* vertexShader;
	/* Application pixel shader. If not set Direct3D is used. */
	IDirect3DPixelShader9* pixelShader;
};

