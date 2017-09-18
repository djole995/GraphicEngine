#pragma once
class D3DMesh
{
public:
	/* Construct D3DMesh object and set device interface. */
	D3DMesh(IDirect3DDevice9* d3dDev);

	~D3DMesh();

	/* Load mesh model from X file. Sets mesh model faces and its materials and textures (class private members). */
	HRESULT LoadMesh(WCHAR* XFilePath);

	/* Render mesh model. */
	void Draw();

protected:
	D3DMATERIAL9* pMeshMaterials;
	IDirect3DTexture9** pMeshTextures;
	ID3DXMesh* mesh;
	IDirect3DDevice9* d3dDev;
	unsigned long numMaterials;
};

