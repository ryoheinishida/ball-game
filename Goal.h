#pragma once
#include "Object.h"
#include "CollisionBox.h"

class Goal : public Object
{
public:
	Goal(DirectXComponent*);
	Goal(DirectXComponent*, D3DXVECTOR3);
	~Goal();
	void Input() override;
	void Update(float deltaTime) override;

public:
	static const float m_Width;
	static const float m_Length;
	static const float m_Height;
};