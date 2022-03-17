#pragma once

#include "Object.h"
#include "DirectXComponent.h"
#include "CollisionBox.h"
#pragma once
#include "Object.h"

class Pin : public Object
{
public:
	Pin(DirectXComponent*);
	Pin(DirectXComponent*,D3DXVECTOR3);
	Pin(DirectXComponent*, D3DXVECTOR3, CollisionBox*);
	~Pin();
	
	void Input() override;
	void Update(float deltaTime) override;
	bool isCollision(D3DXVECTOR3, float);

	//�Փ˔���p�̒�����
	CollisionBox* m_Cb;
	//���S�ʒu
	D3DXVECTOR3 m_CenterPos;
};