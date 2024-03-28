#pragma once

#include "gameObject.h"

class Sprite;
class Audio;

class StageSelect : public GameObject
{
private:
	bool m_Start = false;

	Sprite* m_Cursor = nullptr;
	int m_Select = 0;

	float m_CursorPos[3] = {};
	
	bool m_Active = false;

	Audio* m_SelectSE = nullptr;
	Audio* m_OkSE = nullptr;
public:
	void Init() override;
	void Update() override;
	void Draw() override;

	void SetActive(bool Active) { m_Active = Active; }
	bool GetActive() { return m_Active; }
	bool Start() { return m_Start; }
};