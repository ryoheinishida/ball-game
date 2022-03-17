#include "ShaderInfo.h"
ShaderInfo::~ShaderInfo()
{
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pVertexShader); 
}