#include "Goal.h"

const float Goal::m_Width = 4.0f;
const float Goal::m_Length = 2.5f;
const float Goal::m_Height = 3.0f;

Goal::Goal(DirectXComponent* dxc)
	:Object(dxc)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
	m_TextureName = L"goal.jpg";
	m_ObjectName = "Goal";

	std::vector<D3D10_INPUT_ELEMENT_DESC> layoutConfig = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};
	m_pShaderBlueprint = new ShaderBlueprint(
		{ L"TextureShader.hlsl", L"TextureShader.hlsl", 3, layoutConfig }
	);
	float offset = -0.45;
	std::vector<Vertex> vertices = {
		Vertex{D3DXVECTOR3(m_Width,offset,-m_Length),D3DXVECTOR3(0,1,0),D3DXVECTOR2(1,1)},//頂点1	
		Vertex{D3DXVECTOR3(-m_Width,offset,-m_Length),D3DXVECTOR3(0,1,0),D3DXVECTOR2(0,1)}, //頂点2
		Vertex{D3DXVECTOR3(m_Width,offset,m_Length),D3DXVECTOR3(0,1,0),D3DXVECTOR2(1,0)},  //頂点3
		Vertex{D3DXVECTOR3(-m_Width,offset,m_Length),D3DXVECTOR3(0,1,0),D3DXVECTOR2(0,0)}, //頂点4
		Vertex{D3DXVECTOR3(-m_Width,offset + m_Height,m_Length),D3DXVECTOR3(0,0,-1),D3DXVECTOR2(0,1)},//頂点5	
		Vertex{D3DXVECTOR3(m_Width,offset,m_Length),D3DXVECTOR3(0,0,-1),D3DXVECTOR2(1,0)}, //頂点6
		Vertex{D3DXVECTOR3(m_Width,offset + m_Height,m_Length),D3DXVECTOR3(0,0,-1),D3DXVECTOR2(1,1)},  //頂点7
	};
	std::vector<int> indices = {
		0,1,2,3,4,5,6
	};
	m_pVtxAndIdxBlueprint = new VtxAndIdxBlueprint(
		{ "Goal", "", "", "", vertices, indices, 7, 7 }
	);
	Initialize(dxc);
}

Goal::Goal(DirectXComponent* dxc, D3DXVECTOR3 Pos)
	:Goal(dxc)
{
	m_Pos = Pos;
}

void Goal::Input()
{

}

void Goal::Update(float deltaTime)
{
	m_Pos.z += m_Vel.z * deltaTime;
}

Goal::~Goal()
{
}

