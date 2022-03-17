#pragma once
#include <d3d10.h>
#include <d3dx10.h>
#include <DirectXMath.h>
#include "DirectXComponent.h"
#include "ShaderConstantBuffer.h"
#include "Vertex.h"
#include "Common.h"
#include "RenderComponent.h"
#include "DirectXComponent.h"
#include "TextureInfo.h"
#include "ShaderBlueprint.h"
#include "ShaderInfo.h"
#include "VtxAndIdxBlueprint.h"
#include "VtxAndIdxInfo.h"

#include "ShaderBlueprint.h"
using namespace std;

class RenderComponent;

class Object
{
public:
	Object(DirectXComponent*);
	~Object();
	void Initialize(DirectXComponent*);
	virtual void Input() = 0;
	virtual void Update(float deltaTime) = 0;
	void Render(ID3D10Device*, D3DXMATRIX, D3DXMATRIX, D3DXVECTOR3, D3DXVECTOR3);


public:
	//オブジェクト名
	std::string m_ObjectName;

	//位置・速度
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Vel;
	D3DXVECTOR3 m_Angle;
	D3DXVECTOR3 m_RotVel;
	float m_Scale;

	//色
	D3DXVECTOR4 m_vColor;

	//描画設定用
	LPCWSTR m_TextureName;
	ShaderBlueprint* m_pShaderBlueprint;
	VtxAndIdxBlueprint* m_pVtxAndIdxBlueprint;
	TextureInfo* m_pTextureInfo;
	ShaderInfo* m_pShaderInfo;
	VtxAndIdxInfo* m_pVtxAndIdxInfo;

	RenderComponent* m_pRenderComponent;
};