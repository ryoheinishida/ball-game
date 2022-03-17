#pragma once
#include "Object.h"

class TextBox : public Object
{
public:
	TextBox(DirectXComponent*, LPCWSTR);
	~TextBox();
	void Input() override;
	void Update(float deltaTime) override;

public:
	static const float m_Width;
	static const float m_Height;
};