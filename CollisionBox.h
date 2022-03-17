#pragma once
#include "Common.h"
class CollisionBox
{
public:
	CollisionBox();
	CollisionBox(D3DXVECTOR3, D3DXVECTOR3);
	~CollisionBox();
	bool isCollision(D3DXVECTOR3,float);

public:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Size;
};