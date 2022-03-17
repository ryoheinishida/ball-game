#pragma once

#include "Common.h"
#include "DirectXComponent.h"
#include "TextureContainer.h"
#include "Ball.h"
#include "Stage.h"
#include "Pin.h"
#include "TextBox.h"
#include "Goal.h"
#include "Sky.h"
#include "Green.h"
#include "RenderComponent.h"


class Game
{
public:
	Game();
	~Game();

	//������
	void GenerateObject(DirectXComponent*);
	void DeleteObject();
	HRESULT Initialize(DirectXComponent*);

	//�Q�[���v���O����
	void Loop(DirectXComponent*);
	void Shutdown();
	void App(DirectXComponent*);
	void Input(DirectXComponent*);
	void Update();
	void Scroll();
	void Reset(DirectXComponent*);
	void Render(DirectXComponent*);

public:
	//���W�ϊ��p
	D3DXVECTOR3 m_vEyePt;//���_
	D3DXMATRIX m_View;
	D3DXMATRIX m_Proj;
	D3DXVECTOR3 m_vLight;

	//�Q�[���V�X�e���ϐ�
	float m_ScrollSpeed;
	float m_GoalPos_Z;
	float m_DeltaTime;
	float m_Time;
	float m_StartTime;
	bool m_IsStart;
	bool m_IsGameOver;
	bool m_IsClear;

	//�I�u�W�F�N�g
	Ball* m_Ball;
	std::vector<Object*> m_StageArray;
	Sky* m_Sky;
	Goal* m_Goal;
	std::vector<Pin*> m_PinArray;
	std::vector<Object*> m_ObjectArray;

	//�e�L�X�g
	TextBox* m_StartText;
	TextBox* m_GameOverText;
	TextBox* m_ClearText;
};