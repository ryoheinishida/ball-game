#include "Object.h"


Object::Object(DirectXComponent* dxc)
	: m_ObjectName("")
	, m_pRenderComponent(nullptr)
	, m_TextureName(L"")
	, m_Pos({ 0.0f,0.0f,0.0f })
	, m_Vel({ 0.0f,0.0f,0.0f })
	, m_Angle({ 0.0f,0.0f,0.0f })
	, m_RotVel({ 0.0f,0.0f,0.0f })
	, m_Scale(1.0f)
	, m_vColor({0.5f,0.5f,0.5f,1.0f})
	, m_pShaderBlueprint(nullptr)
	, m_pVtxAndIdxBlueprint(nullptr)
	, m_pTextureInfo(nullptr)
	, m_pShaderInfo(nullptr)
	, m_pVtxAndIdxInfo(nullptr)
{
	m_pRenderComponent = new RenderComponent(this);
}

void Object::Initialize(DirectXComponent* dxc)
{
	if(m_TextureName != L"")m_pTextureInfo = dxc->CreateTextureInfo(m_TextureName);
	m_pShaderInfo = dxc->CreateShaderInfo(m_pShaderBlueprint);
	m_pVtxAndIdxInfo = dxc->CreateVtxAndIdxInfo(m_pVtxAndIdxBlueprint);
	m_pRenderComponent->Initialize(dxc);
}

void Object::Render(ID3D10Device* pDevice, D3DXMATRIX View, D3DXMATRIX Proj, D3DXVECTOR3 vLight, D3DXVECTOR3 vEyePt)
{
	m_pRenderComponent->Render(pDevice, View, Proj, vLight, vEyePt);
}

Object::~Object()
{
	SAFE_DELETE(m_pShaderBlueprint);
	SAFE_DELETE(m_pVtxAndIdxBlueprint);
	SAFE_DELETE(m_pRenderComponent);
}