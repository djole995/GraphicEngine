#pragma once
class D3DMesh
{
public:

	D3DMesh(IDirect3DDevice9* d3dDev);

	~D3DMesh();
	
	HRESULT LoadMesh(WCHAR* XFilePath);
	void Draw();

protected:
	D3DMATERIAL9* pMeshMaterials;
	IDirect3DTexture9** pMeshTextures;
	ID3DXMesh* mesh;
	IDirect3DDevice9* d3dDev;
	unsigned long numMaterials;
};

