#include "stdafx.h"
#include "D3DMesh.h"
#include <atlbase.h>
#include <iostream>


D3DMesh::D3DMesh(IDirect3DDevice9* _d3dDev)
{
	d3dDev = _d3dDev;
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

HRESULT D3DMesh::LoadMesh(WCHAR* XFilePath)
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
		pTextureFilename = L"../Textures/phouse_d.jpg";
		//Create the texture
		if (FAILED(ret = D3DXCreateTextureFromFile(d3dDev,
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
	D3DXMATRIX translateMat;
	// Translate mesh model
	D3DXMatrixTranslation(&translateMat, 0, -4.0, -100);
	D3DXMatrixTranspose(&translateMat, &translateMat);

	d3dDev->SetVertexShaderConstantF(0, translateMat, 4);

	// Actually drawing something here!
	for (DWORD i = 0; i < numMaterials; i++)
	{
		d3dDev->SetMaterial(&pMeshMaterials[i]);
		d3dDev->SetTexture(0, pMeshTextures[i]);

		mesh->DrawSubset(i);
	}
}
