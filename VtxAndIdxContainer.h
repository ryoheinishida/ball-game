#pragma once
#include "Common.h"
#include <d3d10.h>
#include <d3dx10.h>
#include <DirectXMath.h>
#include <map>
#include <vector>
#include <utility>
#include "Vertex.h"
#include "VtxAndIdxBlueprint.h"
#include "VtxAndIdxInfo.h"

struct Vertex;


class VtxAndIdxContainer
{
public:
	VtxAndIdxContainer(ID3D10Device*);
	~VtxAndIdxContainer();
	VtxAndIdxInfo* CreateFromBlueprint(ID3D10Device*, VtxAndIdxBlueprint*);
	void CreateVertexBuffer(ID3D10Device*, Vertex*, int, VtxAndIdxInfo*);
	void CreateIndexBuffer(ID3D10Device*, int*, int, VtxAndIdxInfo*);

public:
	std::map<std::string, int> m_IdxNumArray;
	std::map<std::string, D3DXVECTOR3> m_OffsetArray;//読み込んだモデルを原点に戻すのに必要な情報
	std::map<std::string, std::pair<ID3D10Buffer*, ID3D10Buffer*>> m_BufferArray;
	std::map<std::string, VtxAndIdxInfo*> m_VtxAndIdxArray;
};