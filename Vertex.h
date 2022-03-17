#pragma once
#include <d3dx10.h>
#include <d3d10.h>

struct Vertex
{
	D3DXVECTOR3 Pos;//位置
	D3DXVECTOR3 Normal;//法線ベクトル
	D3DXVECTOR2 Tex;
};