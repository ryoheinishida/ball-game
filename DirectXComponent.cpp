#include "DirectXComponent.h"

DirectXComponent::DirectXComponent()
	: m_hWnd(NULL)
	, m_pDevice(nullptr)
	, m_pSwapChain(nullptr)
	, m_pRenderTargetView(nullptr)
	, m_pDepthStencilView(nullptr)
	, m_pDepthStencil(nullptr)
	, m_pDepthStencilState(nullptr)
	, m_pRasterizerState(nullptr)
	, m_pBlendState(nullptr)
	, m_pSampleLinear(nullptr)
	, m_pTextureContainer(nullptr)
	, m_pShaderContainer(nullptr)
	, m_pVtxAndIdxContainer(nullptr)
	, m_pConstantBuffer(nullptr)
{
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DirectXComponent::MsgProc(hWnd, uMsg, wParam, lParam);
}

LRESULT DirectXComponent::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_KEYDOWN:
		switch ((char)wParam)
		{
		case VK_ESCAPE://ESCキーで終了
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

HRESULT DirectXComponent::Initialize(HINSTANCE hInstance)
{
	if (FAILED(InitWindow(hInstance, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME)))
		return E_FAIL;
	if (FAILED(InitD3D()))
		return E_FAIL;
	if (FAILED(CreateContainer()))
		return E_FAIL;
	return S_OK;
}


HRESULT DirectXComponent::InitWindow(HINSTANCE hInstance,
	INT iX, INT iY, INT iWidth, INT iHeight, LPCWSTR WindowName)
{
	// ウィンドウの定義
	WNDCLASSEX  wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = WindowName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);


	//ウィンドウの作成
	m_hWnd = CreateWindow(WindowName, WindowName, WS_OVERLAPPEDWINDOW,
		0, 0, iWidth, iHeight, 0, 0, hInstance, 0);

	if (!m_hWnd)
	{
		return E_FAIL;
	}
	//ウインドウの表示
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

HRESULT DirectXComponent::InitD3D()
{
	if (FAILED(SetDeviceAndSwapChain()))
		return E_FAIL;
	if (FAILED(SetRenderTargetView()))
		return E_FAIL;
	if (FAILED(SetDepthStencilView()))
		return E_FAIL;
	if (FAILED(SetDepthStencilState()))
		return E_FAIL;
	if (FAILED(SetViewports()))
		return E_FAIL;
	if (FAILED(SetRasterizer()))
		return E_FAIL;
	if (FAILED(SetBlendState()))
		return E_FAIL;
	if (FAILED(SetConstantBuffer()))
		return E_FAIL;
	return S_OK;
}


HRESULT DirectXComponent::SetDeviceAndSwapChain()
{
	// デバイスとスワップチェーンの作成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = WINDOW_WIDTH;
	sd.BufferDesc.Height = WINDOW_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	sd.OutputWindow = m_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	if (FAILED(D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL,
		0, D3D10_SDK_VERSION, &sd, &m_pSwapChain, &m_pDevice)))
	{
		return FALSE;
	}

	return S_OK;
}

HRESULT DirectXComponent::SetRenderTargetView()
{
	ID3D10Texture2D* pBackBuffer;
	if (FAILED(m_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackBuffer)))
	{
		SAFE_DELETE(pBackBuffer);
		return FALSE;
	}
	if (FAILED(m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView)))
	{
		SAFE_DELETE(pBackBuffer);
		return FALSE;
	}
	SAFE_RELEASE(pBackBuffer);
	return S_OK;
}

HRESULT DirectXComponent::SetDepthStencilView()
{
	D3D10_TEXTURE2D_DESC descDepth;
	descDepth.Width = WINDOW_WIDTH;
	descDepth.Height = WINDOW_HEIGHT;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D10_USAGE_DEFAULT;
	descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	if (FAILED(m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pDepthStencil)))
	{
		return FALSE;
	}
	if (FAILED(m_pDevice->CreateDepthStencilView(m_pDepthStencil, NULL, &m_pDepthStencilView)))
	{
		return FALSE;
	}
	//レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド
	m_pDevice->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
	return S_OK;
}

HRESULT DirectXComponent::SetDepthStencilState()
{
	D3D10_DEPTH_STENCIL_DESC dc;
	ZeroMemory(&dc, sizeof(dc));
	dc.DepthEnable = true;
	dc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
	dc.DepthFunc = D3D10_COMPARISON_LESS;
	dc.StencilEnable = false;
	if (FAILED(m_pDevice->CreateDepthStencilState(&dc, &m_pDepthStencilState)))
	{
		return E_FAIL;
	}
	m_pDevice->OMSetDepthStencilState(m_pDepthStencilState, 0);
	return S_OK;
}

HRESULT DirectXComponent::SetViewports()
{
	D3D10_VIEWPORT vp;
	vp.Width = WINDOW_WIDTH;
	vp.Height = WINDOW_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pDevice->RSSetViewports(1, &vp);
	return S_OK;
}

HRESULT DirectXComponent::SetRasterizer()
{
	D3D10_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));
	rdc.CullMode = D3D10_CULL_NONE;
	rdc.FillMode = D3D10_FILL_SOLID;
	rdc.FrontCounterClockwise = TRUE;

	if (FAILED(m_pDevice->CreateRasterizerState(&rdc, &m_pRasterizerState)))
	{
		return FALSE;
	}
	m_pDevice->RSSetState(m_pRasterizerState);
	return S_OK;
}

HRESULT DirectXComponent::SetBlendState()
{
	D3D10_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D10_BLEND_DESC));

	bd.BlendEnable[0] = true;
	bd.SrcBlend = D3D10_BLEND_SRC_ALPHA;
	bd.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	bd.BlendOp = D3D10_BLEND_OP_ADD;
	bd.SrcBlendAlpha = D3D10_BLEND_ONE;
	bd.DestBlendAlpha = D3D10_BLEND_ZERO;
	bd.BlendOpAlpha = D3D10_BLEND_OP_ADD;
	bd.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;

	if (FAILED(m_pDevice->CreateBlendState(&bd, &m_pBlendState)))
		return E_FAIL;

	UINT mask = 0xffffffff;
	m_pDevice->OMSetBlendState(m_pBlendState, NULL, mask);

	return S_OK;
}

HRESULT DirectXComponent::SetSampleLinear()
{
	D3D10_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D10_SAMPLER_DESC));
	SamDesc.Filter = D3D10_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D10_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D10_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D10_TEXTURE_ADDRESS_WRAP;
	m_pDevice->CreateSamplerState(&SamDesc, &m_pSampleLinear);

	return S_OK;
}

HRESULT DirectXComponent::SetConstantBuffer()
{
	D3D10_BUFFER_DESC cb;
	cb.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(ShaderConstantBuffer);
	cb.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.Usage = D3D10_USAGE_DYNAMIC;

	if (FAILED(m_pDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer)))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT DirectXComponent::CreateContainer()
{
	m_pTextureContainer = new TextureContainer(m_pDevice);
	m_pShaderContainer = new ShaderContainer(m_pDevice);
	m_pVtxAndIdxContainer = new VtxAndIdxContainer(m_pDevice);

	return S_OK;
}

TextureInfo* DirectXComponent::CreateTextureInfo(LPCWSTR TextureName)
{
	return m_pTextureContainer->CreateFromTextureName(m_pDevice, TextureName);
}

ShaderInfo* DirectXComponent::CreateShaderInfo(ShaderBlueprint* blueprint)
{
	return m_pShaderContainer->CreateFromBlueprint(m_pDevice, blueprint);
}

VtxAndIdxInfo* DirectXComponent::CreateVtxAndIdxInfo(VtxAndIdxBlueprint* blueprint)
{
	return m_pVtxAndIdxContainer->CreateFromBlueprint(m_pDevice, blueprint);
}

DirectXComponent::~DirectXComponent()
{
	SAFE_DELETE(m_pVtxAndIdxContainer);
	SAFE_DELETE(m_pShaderContainer);
	SAFE_DELETE(m_pTextureContainer);
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pBlendState);
	SAFE_RELEASE(m_pDepthStencilState);
	SAFE_RELEASE(m_pDepthStencil);
	SAFE_RELEASE(m_pRasterizerState);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pRenderTargetView);
	SAFE_RELEASE(m_pDepthStencilView);
	SAFE_RELEASE(m_pDevice);
}