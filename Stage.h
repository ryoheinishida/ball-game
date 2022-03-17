#pragma once
#include "Object.h"
class Object;

class Stage : public Object
{
public:
	Stage(DirectXComponent*);
	Stage(DirectXComponent*, D3DXVECTOR3);
	Stage(LPCWSTR);
	Stage(D3DXVECTOR3, LPCWSTR);
	~Stage();
	
	void Input() override;
	void Update(float deltaTime) override;

	static const float m_Width;
	static const float m_Length;
};