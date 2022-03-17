#include "TextureContainer.h"

TextureContainer::TextureContainer(ID3D10Device* pDevice)
{
}

TextureContainer::~TextureContainer()
{
	for (auto info : m_TextureArray) {
		SAFE_DELETE(info.second);
	}
}

TextureInfo* TextureContainer::CreateFromTextureName(ID3D10Device* pDevice, LPCWSTR texName)
{
	//Šù‚É“Ç‚İ‚İÏ‚İ‚Ì‰æ‘œ‚Ìê‡‚»‚ê‚ğ•Ô‚·
	if (m_TextureArray.count(texName) != 0) {
		return m_TextureArray[texName];
	}
	TextureInfo* ret = new TextureInfo;
	D3DX10CreateShaderResourceViewFromFile(pDevice, texName, NULL, NULL, &ret->m_pTexture, NULL);

	D3D10_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D10_SAMPLER_DESC));
	SamDesc.Filter = D3D10_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D10_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D10_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D10_TEXTURE_ADDRESS_WRAP;
	pDevice->CreateSamplerState(&SamDesc, &ret->m_pSampleLinear);
	
	m_TextureArray.insert({ texName, ret });

	return ret;
}