#include "Game.h"


Game::Game()
	:m_ScrollSpeed(0.001f)
	, m_IsStart(false)
	, m_IsGameOver(false)
	, m_IsClear(false)
	, m_StartTime(timeGetTime() / 1000.0f)
	, m_Time(0.0f)
	, m_DeltaTime(1.0f / 60.0f)
	, m_Ball(nullptr)
	, m_Sky(nullptr)
	, m_Goal(nullptr)
	, m_StartText(nullptr)
	, m_GameOverText(nullptr)
	, m_ClearText(nullptr)
	, m_GoalPos_Z(500.0f)
{
}

Game::~Game()
{
}

void Game::Loop(DirectXComponent* dxc)
{
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT){
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{
			App(dxc);
		}
	}
}

void Game::GenerateObject(DirectXComponent* dxc)
{
	m_Sky = new Sky(dxc);
	std::vector<D3DXVECTOR3> stagePos;
	for (int i = 0; i < 10; i++) {
		stagePos.push_back(D3DXVECTOR3(0, 0, Stage::m_Length * i - 0.1f));
	}
	std::vector<D3DXVECTOR3> greenPos;
	for (int i = 0; i < 10; i++) {
		greenPos.push_back(D3DXVECTOR3(-(Stage::m_Width + Green::m_Width), 0, Green::m_Length * i - 0.1f));
		greenPos.push_back(D3DXVECTOR3((Stage::m_Width + Green::m_Width), 0, Green::m_Length * i - 0.1f));
		greenPos.push_back(D3DXVECTOR3(-(Stage::m_Width + Green::m_Width*2), 0, Green::m_Length * i - 0.1f));
		greenPos.push_back(D3DXVECTOR3((Stage::m_Width + Green::m_Width*2), 0, Green::m_Length * i - 0.1f));
		greenPos.push_back(D3DXVECTOR3(-(Stage::m_Width + Green::m_Width*3), 0, Green::m_Length * i - 0.1f));
		greenPos.push_back(D3DXVECTOR3((Stage::m_Width + Green::m_Width*3), 0, Green::m_Length * i - 0.1f));
	}
	for (auto pos : greenPos) {
		m_ObjectArray.push_back(new Green(dxc, pos));
	}
	for (auto pos : stagePos) {
		m_ObjectArray.push_back(new Stage(dxc, pos));
	}
	m_Ball = new Ball(dxc);
	std::random_device rnd;
	for (int i = 0; i < 10; i++) {
		D3DXVECTOR3 pos = D3DXVECTOR3((rnd() % 11) * 0.5f - 2.5f, 0.0, 5.0f * i + 5.0f);
		m_PinArray.push_back(new Pin(dxc, D3DXVECTOR3(pos)));
	}
	m_Goal = new Goal(dxc, D3DXVECTOR3(0.0f,0.0f,m_GoalPos_Z));

	m_StartText = new TextBox(dxc, L"start_text.png");
	m_GameOverText = new TextBox(dxc, L"game_over_text.png");
	m_ClearText = new TextBox(dxc, L"clear_text.png");
}

void Game::DeleteObject()
{
	while (m_ObjectArray.size() != 0) {
		SAFE_DELETE(m_ObjectArray[m_ObjectArray.size() - 1]);
		m_ObjectArray.pop_back();
	}
	while (m_PinArray.size() != 0) {
		SAFE_DELETE(m_PinArray[m_PinArray.size() - 1]);
		m_PinArray.pop_back();
	}
}

HRESULT Game::Initialize(DirectXComponent* dxc)
{
	GenerateObject(dxc);
	return S_OK;
}

void Game::Shutdown()
{
	SAFE_DELETE(m_ClearText);
	SAFE_DELETE(m_GameOverText);
	SAFE_DELETE(m_StartText);
	SAFE_DELETE(m_Goal);
	SAFE_DELETE(m_Ball);
	SAFE_DELETE(m_Sky);
	DeleteObject();
}

void Game::App(DirectXComponent* dxc)
{
	Input(dxc);
	if (m_IsStart && !(m_IsGameOver || m_IsClear)) {
		Update();
	}
	else {
	}
	Render(dxc);
}

void Game::Input(DirectXComponent *dxc)
{
	if (m_IsGameOver && GetKeyState(VK_RETURN) & 0x80) {
		m_IsGameOver = false;
		Reset(dxc);
	}
	if (m_IsClear && GetKeyState(VK_RETURN) & 0x80) {
		m_IsClear = false;
		Reset(dxc);
	}
	if (!m_IsStart && GetKeyState(VK_RETURN) & 0x80) {
		m_IsStart = true;
	}
	if (m_IsStart && !(m_IsGameOver || m_IsClear)) {
		m_Ball->Input();
		for (auto obj : m_ObjectArray) {
			obj->Input();
		}
		for (auto p : m_PinArray) {
			p->Input();
		}
	}
}

void Game::Update()
{
	while ((timeGetTime() / 1000.0f - m_StartTime) - m_Time < 1.0f / 60.0f) {

	}
	m_DeltaTime = (timeGetTime() / 1000.0f - m_StartTime) - m_Time;
	if (m_DeltaTime > 1.0f / 60.0f) {
		m_DeltaTime = 1.0f / 60.0f;
	}
	m_Time = timeGetTime() / 1000.0f - m_StartTime;
	m_ScrollSpeed = -((m_GoalPos_Z - m_Goal->m_Pos.z) / 10.0f * 1.0f + 1.0f);

	Scroll();
	for (auto obj : m_ObjectArray) {
		obj->Update(m_DeltaTime);
	}
	m_Ball->Update(m_DeltaTime);
	//ボールが画面外に出ていかないように
	if (m_Ball->m_Pos.x < 0.0f) {
		m_Ball->m_Pos.x = fmax(m_Ball->m_Pos.x, -(Stage::m_Width - 1.0f));
	}
	else if (m_Ball->m_Pos.x > 0.0f) {
		m_Ball->m_Pos.x = fmin(m_Ball->m_Pos.x, (Stage::m_Width - 1.0f));
	}
	m_Goal->Update(m_DeltaTime);
	for (auto p : m_PinArray) {
		p->Update(m_DeltaTime);
		//ゴール内にピンが配置されないように
		if (p->m_Pos.z >= m_Goal->m_Pos.z) {
			p->m_Pos.z += 10.0f;
		}
		//近くにあるピンとのみ衝突判定
		if (-m_Ball->m_Radius <= p->m_Pos.z && p->m_Pos.z <= 10.0f) {
			if (p->isCollision(m_Ball->m_Pos, m_Ball->m_Radius)) {
				m_IsGameOver = true;
			}
		}
	}
	//ボールがゴールより後ろならクリア
	if (m_Goal->m_Pos.z <= Goal::m_Length) {
		m_IsClear = true;
	}
}

void Game::Scroll()
{
	m_Ball->m_Vel.z = -m_ScrollSpeed;
	m_Goal->m_Vel.z = m_ScrollSpeed;
	for (auto obj : m_ObjectArray) {
		obj->m_Vel.z = m_ScrollSpeed;
	}
	for (auto p : m_PinArray){
		p->m_Vel.z = m_ScrollSpeed;
	}
}

void Game::Reset(DirectXComponent* dxc)
{
	DeleteObject();
	GenerateObject(dxc);
	m_Ball->m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Goal->m_Pos.z = m_GoalPos_Z;
	m_ScrollSpeed = 0.0f;
}

void Game::Render(DirectXComponent* dxc)
{
	float ClearColor[4] = { 0,0,1,1 };
	dxc->m_pDevice->ClearRenderTargetView(dxc->m_pRenderTargetView, ClearColor);
	dxc->m_pDevice->ClearDepthStencilView(dxc->m_pDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);

	///光源、カメラ位置、視点位置、上方向の設定
	m_vLight = D3DXVECTOR3(-1.0f, 2.0f, 0.0f);
	m_vEyePt = D3DXVECTOR3(0.0f, 2.0f, -4.0f + m_Ball->m_Pos.z);
	D3DXVECTOR3 vLookatPt(0.0f, 0.5f, m_Ball->m_Pos.z + 2.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_View, &m_vEyePt, &vLookatPt, &vUpVec);
	D3DXMatrixPerspectiveFovLH(&m_Proj, D3DX_PI / 3, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);

	m_Sky->Render(dxc->m_pDevice, m_View, m_Proj, m_vLight, m_vEyePt);
	for (auto obj : m_ObjectArray) {
		obj->Render(dxc->m_pDevice, m_View, m_Proj, m_vLight, m_vEyePt);
	}
	m_Ball->Render(dxc->m_pDevice, m_View, m_Proj, m_vLight, m_vEyePt);
	m_Goal->Render(dxc->m_pDevice, m_View, m_Proj, m_vLight, m_vEyePt);

	for (auto obj : m_PinArray) {
		obj->Render(dxc->m_pDevice, m_View, m_Proj, m_vLight, m_vEyePt);
	}

	if (!m_IsStart) {
		m_StartText->Render(dxc->m_pDevice, m_View, m_Proj, m_vLight, m_vEyePt);
	}
	if (m_IsGameOver) {
		m_GameOverText->Render(dxc->m_pDevice, m_View, m_Proj, m_vLight, m_vEyePt);
	}
	if (m_IsClear) {
		m_ClearText->Render(dxc->m_pDevice, m_View, m_Proj, m_vLight, m_vEyePt);
	}
	
	dxc->m_pSwapChain->Present(0, 0);
}