#pragma once
#include "Common.h"
#include "TextureInfo.h"
#include <d3d10.h>
#include <d3dx10.h>
#include <DirectXMath.h>
#include <map>
#include <vector>

//��x�ǂݍ��񂾉摜�̕ێ��p
class TextureContainer
{
public:
	TextureContainer(ID3D10Device*);
	~TextureContainer();
	TextureInfo* CreateFromTextureName(ID3D10Device* ,LPCWSTR);
public:
	std::map<LPCWSTR, TextureInfo*> m_TextureArray;
};