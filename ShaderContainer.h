#pragma once
#include "Common.h"
#include "ShaderInfo.h"
#include "ShaderBluePrint.h"
#include <d3d10.h>
#include <d3dx10.h>
#include <DirectXMath.h>
#include <map>
#include <vector>
#include <utility>

struct Vertex;

//��x�ǂݍ��񂾃V�F�[�_�[�t�@�C����ێ�����
class ShaderContainer
{
public:
	ShaderContainer(ID3D10Device*);
	~ShaderContainer();
	ShaderInfo* CreateFromBlueprint(ID3D10Device*, ShaderBlueprint*);
public:
	std::map<LPCWSTR, ShaderInfo*> m_ShaderArray;
};