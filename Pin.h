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

	//Õ“Ë”»’è—p‚Ì’¼•û‘Ì
	CollisionBox* m_Cb;
	//’†SˆÊ’u
	D3DXVECTOR3 m_CenterPos;
};