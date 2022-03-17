#include "Sky.h"
#include "RenderComponent.h"

const float Sky::m_Width = 180.0f;
const float Sky::m_Length = 60.0f;

Sky::Sky(DirectXComponent* dxc)
	:Object(dxc)
{
	m_Pos = D3DXVECTOR3(0.0f, -2.5f, 90.0f);
	m_TextureName = L"sky.jpg";
	m_ObjectName = "Sky";

	std::vector<D3D10_INPUT_ELEMENT_DESC> layoutConfig = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};
	m_pShaderBlueprint = new ShaderBlueprint(
		{ L"TextureShader.hlsl", L"TextureShader.hlsl", 3, layoutConfig }
	);
	std::vector<Vertex> vertices = {
		Vertex{D3DXVECTOR3(m_Width, -15.0, 0),D3DXVECTOR3(0,1,0),D3DXVECTOR2(1,1)},//頂点1	
		Vertex{D3DXVECTOR3(m_Width, m_Length, 0),D3DXVECTOR3(0,1,0),D3DXVECTOR2(1,0)}, //頂点2
		Vertex{D3DXVECTOR3(-m_Width, -15.0, 0),D3DXVECTOR3(0,1,0),D3DXVECTOR2(0,1)},  //頂点3
		Vertex{D3DXVECTOR3(-m_Width, m_Length, 0),D3DXVECTOR3(0,1,0),D3DXVECTOR2(0,0)} //頂点4	
	};
	std::vector<int> indices = {
		0,1,2,3
	};
	m_pVtxAndIdxBlueprint = new VtxAndIdxBlueprint(
		{ "", "", "", "", vertices, indices, 4, 4 }
	);
	Initialize(dxc);
}

void Sky::Input()
{

}

void Sky::Update(float deltaTime)
{

}

Sky::~Sky()
{
}