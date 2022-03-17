#pragma once
#include "Object.h"

class Sky : public Object
{
public:
	Sky(DirectXComponent*);
	~Sky();
	void Input() override;
	void Update(float deltaTime) override;

public:
	static const float m_Width;
	static const float m_Length;
};