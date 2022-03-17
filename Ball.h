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
	//”¼Œa
	float m_Radius;
	//ƒWƒƒƒ“ƒv’†‚©”Û‚©
	bool m_IsJump;
};