#pragma once
#include "Common.h"
#include "Vertex.h"

struct VtxAndIdxBlueprint
{
	std::string m_ObjName;
	std::string m_StartKeyword;
	std::string m_EndKeyword;
	std::string  m_ObjFileName;
	std::vector<Vertex> m_Vertices;
	std::vector<int> m_Indices;
	int m_VtxNum;
	int m_IdxNum;

public:
	~VtxAndIdxBlueprint();
};