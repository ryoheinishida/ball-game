#pragma once
#include "Common.h"
#include "ShaderConstantBuffer.h"
#include "TextureContainer.h"
#include "ShaderContainer.h"
#include "VtxAndIdxContainer.h"
#include "ShaderBluePrint.h"
#include "ShaderInfo.h"
#include "VtxAndIdxBlueprint.h"
#include "VtxAndIdxInfo.h"
#include "TextureInfo.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960
#define APP_NAME L"ボウリング"

class DirectXComponent
{
public:
	DirectXComponent();
	~DirectXComponent();

	HRESULT InitD3D();
	HRESULT Initialize(HINSTANCE);
	HRESULT InitWindow(HINSTANCE, INT, INT, INT, INT, LPCWSTR);
	static LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);


	HRESULT SetDeviceAndSwapChain();
	HRESULT SetRenderTargetView();
	HRESULT SetDepthStencilView();
	HRESULT SetViewports();
	HRESULT SetRasterizer();
	HRESULT SetDepthStencilState();
	HRESULT SetBlendState();
	HRESULT SetSampleLinear();
	HRESULT SetConstantBuffer();
	HRESULT CreateContainer();

	TextureInfo* CreateTextureInfo(LPCWSTR);
	ShaderInfo* CreateShaderInfo(ShaderBlueprint*);
	VtxAndIdxInfo* CreateVtxAndIdxInfo(VtxAndIdxBlueprint*);

public:
	//ウィンドウ
	HWND m_hWnd;

	//DirectX関連
	ID3D10Device* m_pDevice;
	IDXGISwapChain* m_pSwapChain;
	ID3D10RenderTargetView* m_pRenderTargetView;
	ID3D10DepthStencilView* m_pDepthStencilView;
	ID3D10Texture2D* m_pDepthStencil;
	ID3D10DepthStencilState* m_pDepthStencilState;
	ID3D10RasterizerState* m_pRasterizerState;
	ID3D10BlendState* m_pBlendState;
	ID3D10SamplerState* m_pSampleLinear;
	ID3D10Buffer* m_pConstantBuffer;

	//一度読み込んだファイルを保持
	TextureContainer* m_pTextureContainer;
	ShaderContainer* m_pShaderContainer;
	VtxAndIdxContainer* m_pVtxAndIdxContainer;
};