#pragma once
#include <d3d10.h>
#include <d3dx10.h>

struct ShaderConstantBuffer
{
	D3DXMATRIX mW;
	D3DXMATRIX mWVP;
	D3DXVECTOR4 vLightDir;
	D3DXVECTOR4 vColor;
	D3DXVECTOR4 vEye;
};