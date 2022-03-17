#include "Ball.h"

Ball::Ball(DirectXComponent* dxc)
	: Object(dxc)
	,m_Radius(0.5f)
	,m_IsJump(false)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Vel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotVel = D3DXVECTOR3(1.0f,0.0f,0.0f);
	m_Angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TextureName = L"";
	m_ObjectName = "Ball";

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
		{ "Ball", "ball", "rings", "bowling.obj", vertices, indices, 0, 0 }
	);
	Initialize(dxc);
}

void Ball::Input()
{
	if (GetKeyState(VK_RIGHT) & 0x800 && !m_IsJump) {
		m_Angle.y += DirectX::XMConvertToRadians(m_RotVel.y);
		m_Angle.y = fmin(m_Angle.y, DirectX::XMConvertToRadians(45.0f));
	}
	else if (GetKeyState(VK_LEFT) & 0x800 && !m_IsJump) {
		m_Angle.y -= DirectX::XMConvertToRadians(m_RotVel.y);
		m_Angle.y = fmax(m_Angle.y, -DirectX::XMConvertToRadians(45.0f));
	}
}

void Ball::Jump(float deltaTime)
{
	const float max_Vel = 20.0f;
	const float acceleration = max_Vel / 10.0f;
	if (m_Vel.y == 0.0f && m_Pos.y == 0.0f) {
		m_Vel.y = max_Vel;
	}
	m_Pos.y += m_Vel.y * deltaTime;
	m_Vel.y -= acceleration;
	if (m_Vel.y <= -max_Vel) {
		m_Vel.y = 0.0f;
		m_Pos.y = 0.0f;
		m_IsJump = false;
	}
}

void Ball::Update(float deltaTime)
{
	m_Vel.x = sin(m_Angle.y) * m_Vel.z;
	m_Pos.x += m_Vel.x * deltaTime;
	m_RotVel.y = fmax(2.0f, m_RotVel.y + 0.01f * deltaTime);
	m_RotVel.z = timeGetTime() / 100.0f;
	if (GetKeyState(VK_SPACE) & 0x800) {
		if (m_Pos.y == 0.0f && !m_IsJump) {
			m_IsJump = true;
		}
	}
	if (m_IsJump) {
		Jump(deltaTime);
	}

}

Ball::~Ball()
{
}
