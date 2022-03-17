#pragma once
#include "Object.h"

class Green : public Object
{
public:
	Green(DirectXComponent*);
	Green(DirectXComponent*, D3DXVECTOR3);
	~Green();
	void Input() override;
	void Update(float deltaTime) override;

public:
	static const float m_Width;
	static const float m_Length;
};