#include "cube.h"
#include "shader.h"
using namespace D3D;
using namespace MyCube;

const float Rotation = D3DX_PI/24;

Cube::Cube(): r(3.0f), tetha(D3DX_PI/3), phi(D3DX_PI/6)
{
};

HRESULT Cube::InitialObject()
{
	const float coord = 0.5f;
	CUSTOMVERTEX Vertex[] = 
	{
		{coord, coord, -coord,        RED},	
		{coord, coord, coord,       BLACK},	
		{-coord, coord, -coord,   MAGENTA},	
		{-coord, coord, coord,     YELLOW},		

		{-coord, -coord, -coord,    GREEN},		
		{-coord, -coord, coord,     WHITE},	
		{coord, -coord, -coord,      CYAN},		
		{coord, -coord, coord,       BLUE}
	};
	CountVertex = sizeof(Vertex) / sizeof( Vertex[0] );
	if (S_OK != device.InitialVertexBuffer(Vertex, CountVertex))
	{
		return E_FAIL;
	}
	CUSTOMINDEX Index[] = 
	{
		0, 2, 3,		0, 3, 1, //top
		2, 4, 5,		2, 5, 3, //left
		4, 6, 7,		4, 7, 5, //bottom
		6, 0, 1,		6, 1, 7, //right
		1, 3, 5,		1, 5, 7, //back
		4, 2, 0,		4, 0, 6, //front
	};
	CountIndex = sizeof(Index) / sizeof( Index[0] );
	if (S_OK != device.InitialIndexBuffer(Index, CountIndex))
	{
		return E_FAIL;
	}
	return S_OK;
}

void Cube::Draw()
{
	if (NULL==device.pDirect3D)
	{
		return;
	}
	device.pDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 100, 150), 1.0f, 0);
	device.pDirect3DDevice->BeginScene();
	if (S_OK == device.matrix.SetMatrix(r, tetha, phi))
	{
		device.pDirect3DDevice->SetStreamSource(0, device.pVertexBuffer, 0, sizeof(CUSTOMVERTEX));
		device.pDirect3DDevice->SetIndices(device.pIndexBuffer);
		device.pDirect3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, CountVertex, 0, CountIndex/3); 
	}

	device.pDirect3DDevice->EndScene();
	device.pDirect3DDevice->Present(NULL, NULL, NULL, NULL);
}

Cube::~Cube()
{
}

void Cube::Move(float x, Coords alpha)
{
	switch (alpha)
	{
	case TETHA:
		tetha+=(Rotation)*x;
		break;
	case PHI:
		phi+= (Rotation)*x;
		break;
	};
}