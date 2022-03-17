#pragma once
#include "Common.h"

struct VtxAndIdxInfo
{
	int m_IndexNum;
	D3DXVECTOR3 m_Offset;
	ID3D10Buffer* m_pVertexBuffer;
	ID3D10Buffer* m_pIndexBuffer;

public:
	~VtxAndIdxInfo();
};