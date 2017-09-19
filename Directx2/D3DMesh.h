#pragma once
class D3DMesh
{
public:
	/* Construct D3DMesh object and set device interface and init position with parameter values. */
	D3DMesh(IDirect3DDevice9* d3dDev, int x = 0, int y = 0, int z = 0);

	~D3DMesh();

	/* Load mesh model from X file. Sets mesh model faces and its materials and textures (class private members). */
	HRESULT LoadMesh(WCHAR* XFilePath, LPCWSTR texturePaths[]);

	/* Render mesh model. */
	void Draw();

protected:
	D3DMATERIAL9* pMeshMaterials;
	IDirect3DTexture9** pMeshTextures;
	ID3DXMesh* mesh;
	IDirect3DDevice9* d3dDev;
	unsigned long numMaterials;
	D3DXMATRIX matTranslate;
	D3DXMATRIX matRotateX;
	D3DXMATRIX matRotateY;
	D3DXMATRIX matRotateZ;
	D3DXMATRIX matScale;
};

