#include "RenderComponent.h"

RenderComponent::RenderComponent(Object* owner)
{
	m_pOwner = owner;
}

RenderComponent::~RenderComponent()
{
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

void RenderComponent::Initialize(DirectXComponent* dxc)
{
	m_pVertexShader = m_pOwner->m_pShaderInfo->m_pVertexShader;
	m_pVertexLayout = m_pOwner->m_pShaderInfo->m_pVertexLayout;
	m_pPixelShader = m_pOwner->m_pShaderInfo->m_pPixelShader;

	if (m_pOwner->m_TextureName != L"") {
		m_pTexture = m_pOwner->m_pTextureInfo->m_pTexture;
		m_pSampleLinear = m_pOwner->m_pTextureInfo->m_pSampleLinear;
	}

	m_pConstantBuffer = dxc->m_pConstantBuffer;

	m_pVertexBuffer = m_pOwner->m_pVtxAndIdxInfo->m_pVertexBuffer;
	m_pIndexBuffer = m_pOwner->m_pVtxAndIdxInfo->m_pIndexBuffer;
	m_IndexNum = m_pOwner->m_pVtxAndIdxInfo->m_IndexNum;
	m_Offset = m_pOwner->m_pVtxAndIdxInfo->m_Offset;
}

void RenderComponent::Render(ID3D10Device* pDevice, D3DXMATRIX View, D3DXMATRIX Proj, D3DXVECTOR3 vLight, D3DXVECTOR3 vEyePt)
{
	D3DXMATRIX mWorld, mTrans, mRot, mScale;
	D3DXMatrixIdentity(&mWorld);

	//オフセット分の移動
	D3DXMatrixTranslation(&mTrans, -m_Offset.x, -m_Offset.y, -m_Offset.z);
	D3DXMatrixMultiply(&mWorld, &mWorld, &mTrans);

	//ボールのみ
	//初期状態で正面を向くように調整
	if (m_pOwner->m_ObjectName == "Ball") {

		D3DXMatrixRotationY(&mRot, DirectX::XMConvertToRadians(146.0f));
		D3DXMatrixMultiply(&mWorld, &mWorld, &mRot);
		D3DXMatrixRotationZ(&mRot, DirectX::XMConvertToRadians(214.5f));
		D3DXMatrixMultiply(&mWorld, &mWorld, &mRot);
		D3DXMatrixRotationX(&mRot, DirectX::XMConvertToRadians(45.0f));
		D3DXMatrixMultiply(&mWorld, &mWorld, &mRot);
	}
	

	//拡大・縮小
	D3DXMatrixScaling(&mScale, m_pOwner->m_Scale, m_pOwner->m_Scale, m_pOwner->m_Scale);
	D3DXMatrixMultiply(&mWorld, &mWorld, &mScale);

	//回転
	//ボールのみ複数軸回転が必要なのでその処理
	if (m_pOwner->m_ObjectName == "Ball") {
		D3DXMatrixRotationY(&mRot, m_pOwner->m_Angle.y);
		D3DXMatrixMultiply(&mWorld, &mWorld, &mRot);
		const D3DXVECTOR3 Axis = D3DXVECTOR3(cos(m_pOwner->m_Angle.y), 0, -sin(m_pOwner->m_Angle.y));
		D3DXMatrixRotationAxis(&mRot, &Axis, m_pOwner->m_RotVel.z);
		D3DXMatrixMultiply(&mWorld, &mWorld, &mRot);
	}
	else {

	}

	//移動
	D3DXMatrixTranslation(&mTrans, m_pOwner->m_Pos.x, m_pOwner->m_Pos.y, m_pOwner->m_Pos.z);
	D3DXMatrixMultiply(&mWorld, &mWorld, &mTrans);

	//シェーダーの登録
	ShaderConstantBuffer* pcb;
	pDevice->VSSetShader(m_pVertexShader);
	pDevice->PSSetShader(m_pPixelShader);

	if (SUCCEEDED(m_pConstantBuffer->Map(D3D10_MAP_WRITE_DISCARD, NULL, (void**)&pcb)))
	{
		pcb->mW = mWorld;
		D3DXMatrixTranspose(&pcb->mW, &pcb->mW);
		D3DXMATRIX m = mWorld * View * Proj;
		pcb->mWVP = m;
		D3DXMatrixTranspose(&pcb->mWVP, &pcb->mWVP);

		pcb->vLightDir = static_cast<D3DXVECTOR4>(vLight);

		//カラーを渡す
		pcb->vColor = m_pOwner->m_vColor;

		//視点位置を渡す
		pcb->vEye = D3DXVECTOR4(vEyePt.x, vEyePt.y, vEyePt.z, 0);
		m_pConstantBuffer->Unmap();
	}


	//使用するシェーダーの登録
	pDevice->VSSetShader(m_pVertexShader);
	pDevice->PSSetShader(m_pPixelShader);
	//コンスタントバッファーを使うシェーダーの登録
	pDevice->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	pDevice->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//頂点インプットレイアウトをセット
	pDevice->IASetInputLayout(m_pVertexLayout);

	pDevice->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	if (m_pOwner->m_pVtxAndIdxBlueprint->m_ObjFileName != "") {
		pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	else {
		pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
	//頂点バッファーをセット
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	pDevice->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	pDevice->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	if (m_pOwner->m_TextureName) {
		pDevice->PSSetSamplers(0, 1, &m_pSampleLinear);
		pDevice->PSSetShaderResources(0, 1, &m_pTexture);
	}

	pDevice->DrawIndexed(m_IndexNum, 0, 0);
}