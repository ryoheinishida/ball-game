#include "Pin.h"

Pin::Pin(DirectXComponent *dxc)
	:Object(dxc)
	,m_Cb(nullptr)

{
	m_Scale = 0.5f;
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Vel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotVel = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_Angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vColor = D3DXVECTOR4(1.0f,1.0f,0.0f,0.0f);
	m_TextureName = L"";
	m_ObjectName = "Pin";

	std::vector<D3D10_INPUT_ELEMENT_DESC> layoutConfig = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};
	m_pShaderBlueprint = new ShaderBlueprint(
		{ L"NoTextureShader.hlsl", L"NoTextureShader.hlsl", 2, layoutConfig }
	);
	std::vector<Vertex> vertices = {
	};
	std::vector<int> indices = {
	};
	m_pVtxAndIdxBlueprint = new VtxAndIdxBlueprint(
		{ "Pin", "pin", "", "bowling.obj", vertices, indices, 0, 0 }
	);
	Initialize(dxc);
}

Pin::Pin(DirectXComponent *dxc, D3DXVECTOR3 Pos)
	:Pin(dxc)
{
	m_Pos = Pos;
	m_Cb = new CollisionBox(m_Pos, D3DXVECTOR3(0.2f,0.5f,0.2f));
}

Pin::Pin(DirectXComponent *dxc, D3DXVECTOR3 Pos, CollisionBox* Cb) 
	:Pin(dxc, Pos)
{
	m_Cb = Cb;
}

void Pin::Input()
{

}

void Pin::Update(float deltaTime)
{
	m_Pos.z += m_Vel.z * deltaTime;
	if (m_Pos.z <= -5.0f) {
		std::random_device rand;
		m_Pos.x = (rand() % 11) * 0.5f - 2.5f;
		m_Pos.z = 45.0f;
	}
	m_Cb->m_Pos.x = m_Pos.x;
	m_Cb->m_Pos.z = m_Pos.z;
}

bool Pin::isCollision(D3DXVECTOR3 ball_Pos, float ball_Radius)
{
	if (m_Cb->isCollision(ball_Pos, ball_Radius)) {
		return true;
	}
	return false;
}

Pin::~Pin()
{
	SAFE_DELETE(m_Cb);
}