#include "TextBox.h"

const float TextBox::m_Width = 5.0f;
const float TextBox::m_Height = 1.0f;

TextBox::TextBox(DirectXComponent* dxc, LPCWSTR textureName)
	:Object(dxc)
{
	m_TextureName = textureName;
	m_ObjectName = "TextBox";

	std::vector<D3D10_INPUT_ELEMENT_DESC> layoutConfig = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};
	m_pShaderBlueprint = new ShaderBlueprint(
		{ L"TextureShader.hlsl", L"TextureShader.hlsl", 3, layoutConfig }
	);
	std::vector<Vertex> vertices = {
		Vertex{D3DXVECTOR3(-m_Width / 2,1.0 + m_Height,1.0),D3DXVECTOR3(0,1,1),D3DXVECTOR2(0,0)},//頂点1	
		Vertex{D3DXVECTOR3(-m_Width / 2,1.0,1.0),D3DXVECTOR3(0,1,1),D3DXVECTOR2(0,1)}, //頂点2
		Vertex{D3DXVECTOR3(m_Width / 2,1.0 + m_Height,1.0), D3DXVECTOR3(0,1,1),D3DXVECTOR2(1,0)},  //頂点3
		Vertex{D3DXVECTOR3(m_Width / 2,1.0,1.0),D3DXVECTOR3(0,1,1),D3DXVECTOR2(1,1)} //頂点4	
	};
	std::vector<int> indices = {
		0,1,2,3
	};
	m_pVtxAndIdxBlueprint = new VtxAndIdxBlueprint(
		{ "TextBox", "", "", "", vertices, indices, 4, 4 }
	);
	Initialize(dxc);
}

TextBox::~TextBox()
{
}
 
void TextBox::Input()
{

}
void TextBox::Update(float deltaTime)
{
	
}