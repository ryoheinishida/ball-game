#pragma once
#include "Common.h"
struct ShaderInfo
{
	ID3D10VertexShader* m_pVertexShader;
	ID3D10PixelShader* m_pPixelShader;
	ID3D10InputLayout* m_pVertexLayout;
public:
	~ShaderInfo();
};