#pragma once
#include "Object.h"
#include "RenderComponent.h"
#include "DirectXComponent.h"

class Pin;

class Ball : public Object
{
public:
	Ball(DirectXComponent*);
	~Ball();
	void Input() override;
	void Update(float) override;
	void Jump(float);

public:
	//���a
	float m_Radius;
	//�W�����v�����ۂ�
	bool m_IsJump;
};