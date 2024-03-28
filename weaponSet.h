#pragma once

#include "gameObject.h"

class Sprite;
class Audio;

class WeaponSet : public GameObject
{
private:
	Sprite* m_Cursor[2] = {};
	Sprite* m_WeaponView[6] = {};

	float m_CursorPos[3] = {};
	int m_Select[2] = {};
	int m_MainSub = 0;//0:main,1:sub
	bool m_Active = false;

	Audio* m_SelectSE = nullptr;
	Audio* m_OkSE = nullptr;
public:
	void Init() override;
	void Update() override;
	void Draw() override;

	void SetActive(bool Active) { m_Active = Active; }
	bool GetActive() { return m_Active; }
};