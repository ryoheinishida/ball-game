#include "ShaderContainer.h"

ShaderContainer::ShaderContainer(ID3D10Device* pDevice)
{
}

ShaderContainer::~ShaderContainer()
{
	for (auto shader : m_ShaderArray) {
		SAFE_DELETE(shader.second);
	}
}

ShaderInfo* ShaderContainer::CreateFromBlueprint(ID3D10Device* pDevice, ShaderBlueprint* blueprint)
{
	//既に読み込み済みの場合それを返す
	if (m_ShaderArray.count(blueprint->m_VS_FileName) != 0) {
		return m_ShaderArray[blueprint->m_VS_FileName];
	}

	ShaderInfo* ret = new ShaderInfo;

	ID3D10Blob* pCompiledShader = nullptr;
	ID3D10Blob* pErrors = NULL;
	ID3D10VertexShader* pVertexShader = nullptr;
	if (FAILED(D3DX10CompileFromFile(blueprint->m_VS_FileName, NULL, NULL, "VS", "vs_4_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
	{
		SAFE_RELEASE(pErrors);
		MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &ret->m_pVertexShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"バーテックスシェーダー作成失敗", NULL, MB_OK);
		exit(0);
	}

	ID3D10InputLayout* pVertexLayout = nullptr;
	D3D10_INPUT_ELEMENT_DESC* layout = new D3D10_INPUT_ELEMENT_DESC[blueprint->m_LayoutNum];
	for (int i = 0; i < blueprint->m_LayoutNum; i++) {
		layout[i] = blueprint->m_LayoutConfig[i];
	}

	if (FAILED(pDevice->CreateInputLayout(layout, blueprint->m_LayoutNum, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &ret->m_pVertexLayout)))
	{
		MessageBox(0, L"レイアウト作成失敗", NULL, MB_OK);
		exit(0);
	}

	ID3D10PixelShader* pPixelShader;
	//ブロブからピクセルシェーダー作成
	if (FAILED(D3DX10CompileFromFile(blueprint->m_PS_FileName, NULL, NULL, "PS", "ps_4_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
	{
		SAFE_RELEASE(pErrors);
		MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
	}
	SAFE_RELEASE(pErrors);
	if (FAILED(pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &ret->m_pPixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"ピクセルシェーダー作成失敗", NULL, MB_OK);
	}

	m_ShaderArray.insert({ blueprint->m_VS_FileName,ret });

	SAFE_RELEASE(pCompiledShader);
	SAFE_DELETE_ARRAY(layout);

	return ret;
}