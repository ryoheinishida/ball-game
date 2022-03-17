#include "VtxAndIdxInfo.h"
VtxAndIdxInfo::~VtxAndIdxInfo()
{
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pVertexBuffer);
}
