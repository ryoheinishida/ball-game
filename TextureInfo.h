#pragma once
#include "Common.h"
struct TextureInfo
{
	ID3D10ShaderResourceView* m_pTexture;
	ID3D10SamplerState* m_pSampleLinear;
public:
	~TextureInfo();
};