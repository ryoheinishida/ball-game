#include "TextureInfo.h"

TextureInfo::~TextureInfo()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSampleLinear);
}