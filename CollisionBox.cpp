#include "CollisionBox.h"

CollisionBox::CollisionBox()
	:m_Pos(D3DXVECTOR3(0.0f,0.0f,0.0f))
	,m_Size(D3DXVECTOR3(0.0f,0.0f,0.0f))
{

}

CollisionBox::CollisionBox(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	m_Pos = Pos;
	m_Size = Size;
}

bool CollisionBox::isCollision(D3DXVECTOR3 ball_Pos, float ball_Radius)
{
	float distance = 0.0f;
	if (ball_Pos.x <= (m_Pos.x - m_Size.x / 2.0f) || (m_Pos.x + m_Size.x / 2.0f) <= ball_Pos.x) {
		float d_X = fmin(fabs(ball_Pos.x - (m_Pos.x - m_Size.x / 2.0f)), fabs(ball_Pos.x - (m_Pos.x + m_Size.x / 2.0f)));
		distance += d_X * d_X;
	}
	if (ball_Pos.y <= (m_Pos.y - m_Size.y / 2.0f) || (m_Pos.y + m_Size.y / 2.0f) <= ball_Pos.y) {
		float d_Y = fmin(fabs(ball_Pos.y - (m_Pos.y - m_Size.y / 2.0f)), fabs(ball_Pos.y - (m_Pos.y + m_Size.y / 2.0f)));
		distance += d_Y * d_Y;
	}
	if (ball_Pos.z <= (m_Pos.z - m_Size.z / 2.0f) || (m_Pos.z + m_Size.z / 2.0f) <= ball_Pos.z) {
		float d_Z = fmin(fabs(ball_Pos.z - (m_Pos.z - m_Size.z / 2.0f)), fabs(ball_Pos.z - (m_Pos.z + m_Size.z / 2.0f)));
		distance += d_Z * d_Z;
	}

	if (distance <= ball_Radius * ball_Radius) {
		return true;
	}
	return false;
}

CollisionBox::~CollisionBox()
{

}