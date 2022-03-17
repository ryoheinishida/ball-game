#pragma once
#include "Common.h"
#include "Object.h"
#include "DirectXComponent.h"
#include "Vertex.h"
#include <typeinfo>
#include <string>

class Object;

class RenderComponent
{
public:
	//RenderComponent(Object*);
	RenderComponent(Object*);
	~RenderComponent();
	void Initialize(DirectXComponent*);
	void Render(ID3D10Device*, D3DXMATRIX, D3DXMATRIX, D3DXVECTOR3, D3DXVECTOR3);

public:
	ID3D10InputLayout* m_pVertexLayout;
	ID3D10VertexShader* m_pVertexShader;
	ID3D10PixelShader* m_pPixelShader;
	ID3D10Buffer* m_pVertexBuffer;
	ID3D10Buffer* m_pIndexBuffer;
	ID3D10Buffer* m_pConstantBuffer;

	//テクスチャ関連
	ID3D10ShaderResourceView* m_pTexture;
	ID3D10SamplerState* m_pSampleLinear;
	LPCWSTR m_TextureName;

	//頂点情報
	Vertex* m_Vertices;
	int m_VertexNum;
	int* m_Indices;
	int m_IndexNum;

	//シェーダーファイル名
	LPCWSTR m_VS_FileName;
	LPCWSTR m_PS_FileName;

	//オフセット
	D3DXVECTOR3 m_Offset;

	//所有されるオブジェクト
	Object* m_pOwner;
};