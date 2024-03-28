#pragma once

#include "gameObject.h"

class Plate;

class Item : public GameObject
{
private:
	Plate* m_Plate = nullptr;
	float m_Heal;

public:
	void Init(D3DXVECTOR3 Position);
	void Uninit();
	void Update();
	void Draw();
};