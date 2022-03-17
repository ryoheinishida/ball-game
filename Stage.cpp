#include "Stage.h"
#include "DirectXComponent.h"

const float Stage::m_Width = 4.0f;
const float Stage::m_Length = 10.0f;

Stage::Stage(DirectXComponent *dxc)
	:Object(dxc)
{
	m_TextureName = L"asphalt.jpg";
	m_ObjectName = "Stage";

	std::vector<D3D10_INPUT_ELEMENT_DESC> layoutConfig = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};
	m_pShaderBlueprint = new ShaderBlueprint(
		{ L"TextureShader.hlsl", L"TextureShader.hlsl", 2, layoutConfig }
	);
	std::vector<Vertex> vertices = {
		Vertex{D3DXVECTOR3(m_Width,-0.5,-m_Length),D3DXVECTOR3(0,1,0),D3DXVECTOR2(1,1)},//頂点1	
		Vertex{D3DXVECTOR3(m_Width,-0.5,m_Length),D3DXVECTOR3(0,1,0),D3DXVECTOR2(1,0)}, //頂点2
		Vertex{D3DXVECTOR3(-m_Width,-0.5,-m_Length),D3DXVECTOR3(0,1,0),D3DXVECTOR2(0,1)},  //頂点3
		Vertex{D3DXVECTOR3(-m_Width,-0.5,m_Length),D3DXVECTOR3(0,1,0),D3DXVECTOR2(0,0)} //頂点4	
	};
	std::vector<int> indices = {
		0,1,2,3
	};
	m_pVtxAndIdxBlueprint = new VtxAndIdxBlueprint(
		{ "Stage", "", "", "", vertices, indices, 4, 4 }
	);
	Initialize(dxc);
	
}

Stage::Stage(DirectXComponent *dxc, D3DXVECTOR3 Pos)
	:Stage(dxc)
{
	m_Pos = Pos;
}

void Stage::Input()
{
}

void Stage::Update(float deltaTime)
{
	m_Pos.z += m_Vel.z * deltaTime;
	if (m_Pos.z <= -6.0f) {
		m_Pos.z = 98.0f;
	}
}

Stage::~Stage()
{
}