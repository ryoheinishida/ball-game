#pragma once
#include "Common.h"
struct ShaderBlueprint
{
	LPCWSTR m_VS_FileName;
	LPCWSTR m_PS_FileName;
	const UINT m_LayoutNum;
	std::vector<D3D10_INPUT_ELEMENT_DESC> m_LayoutConfig;

public:
	~ShaderBlueprint();
};

