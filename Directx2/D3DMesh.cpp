#include "stdafx.h"
#include "D3DMesh.h"
#include <atlbase.h>
#include <iostream>


D3DMesh::D3DMesh(IDirect3DDevice9* _d3dDev, int x, int y, int z)
{
 	d3dDev = _d3dDev;
	D3DXMatrixTranslation(&matTranslate, x, y, z);
	D3DXMatrixIdentity(&matRotateX);
	D3DXMatrixIdentity(&matRotateY);
	D3DXMatrixIdentity(&matRotateZ);
	D3DXMatrixIdentity(&matScale);
}


D3DMesh::~D3DMesh()
{
	// Tidy up!
	for (DWORD i = 0; i < numMaterials; i++)
	{
		if (pMeshTextures[i] != NULL)
			pMeshTextures[i]->Release();
	}
	delete[] pMeshMaterials;
	delete[] pMeshTextures;
	mesh->Release();  // ** BUG FIX!  DONT FORGET TO RELEASE RESOURCES
}

HRESULT D3DMesh::LoadMesh(WCHAR* XFilePath, LPCWSTR texturesPaths[])
{
	USES_CONVERSION;
	LPD3DXBUFFER pMtrlBuffer = NULL;
	LPD3DXBUFFER eff;
	HRESULT ret;

	ret = D3DXLoadMeshFromX(XFilePath, D3DXMESH_SYSTEMMEM, d3dDev, NULL, &pMtrlBuffer, &eff, &numMaterials, &mesh);
	if (FAILED(ret))
		return ret;

	pMeshMaterials = new D3DMATERIAL9[numMaterials];
	pMeshTextures = new LPDIRECT3DTEXTURE9[numMaterials];
	D3DXMATERIAL* matMaterials = (D3DXMATERIAL*)pMtrlBuffer->GetBufferPointer();
	// Loads of allocation etc here!
	for (DWORD i = 0; i < numMaterials; i++)
	{
		//Copy the material
		pMeshMaterials[i] = matMaterials[i].MatD3D;
		//Set the ambient color for the material (D3DX does not do this)
		pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;

		LPCWSTR pTextureFilename = A2W(matMaterials[i].pTextureFilename);
		
		/* Hardcoded because current test X file does not have well set texture path. */
		pTextureFilename = texturesPaths[i];

		//Create the texture
		if (FAILED(D3DXCreateTextureFromFile(d3dDev,
			pTextureFilename,
			&pMeshTextures[i])))
		{
			return ret;
		}
	}

	pMtrlBuffer->Release();

	return ret;
}

void D3DMesh::Draw()
{
	D3DXMatrixTranspose(&matTranslate, &matTranslate);
	d3dDev->SetVertexShaderConstantF(0, matTranslate, 4);
	D3DXMatrixTranspose(&matTranslate, &matTranslate);

	// Actually drawing something here!
	for (DWORD i = 0; i < numMaterials; i++)
	{
		d3dDev->SetMaterial(&pMeshMaterials[i]);
		d3dDev->SetTexture(0, pMeshTextures[i]);

		mesh->DrawSubset(i);
	}
}
