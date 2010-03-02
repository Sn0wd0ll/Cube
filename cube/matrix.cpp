#include "directx9.h"
using namespace D3D;

Matrix::Matrix():at(0, 0, 0), eye(3, 3, 3), up(0, 1, 0)
{}

Matrix::~Matrix()
{}

HRESULT Matrix::SetMatrix(float r, float tetha, float phi)
{
	eye.x = r*sin(tetha)*cos(phi);
	eye.y = r*sin(tetha)*sin(phi);
	eye.z = r*cos(tetha);
	D3DXVECTOR3 x;
	D3DXVECTOR3 y;
	D3DXVECTOR3 z;
	z = at - eye;
	D3DXVec3Normalize(&z, &z);
	D3DXVec3Cross(&x, &up, &z);
	D3DXVec3Normalize(&x, &x);

	D3DXVec3Cross(&y, &z, &x);

	D3DXMATRIX ViewMatrix (x.x, x.y, x.z, -D3DXVec3Dot(&eye, &x),
						   y.x, y.y, y.z, -D3DXVec3Dot(&eye, &y),
						   z.x, z.y, z.z, -D3DXVec3Dot(&eye, &z),
						   0,   0,   0,   1);
    const float M = 1.0f;
    const float F = 20.0f;
    float a = F/(F - M);
    float b = -M * a;
	D3DXMATRIX ProjMatrix (M, 0,  0,  0,
					       0, M,  0,  0,
					       0, 0,  a,  b,
					       0, 0,  1,  0);

	D3DXMATRIX WorldMatrix = ProjMatrix * ViewMatrix;
	device->shader.SetShader(WorldMatrix);

	return S_OK;
}
