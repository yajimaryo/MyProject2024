#pragma once

#include "gameObject.h"

class Sprite;

class GameClear : public GameObject
{
private:
	bool m_IsClear;

	Sprite* m_ClearSprite = nullptr;
	Sprite* m_LoseSprite = nullptr;

	float m_Alpha = 0.0f;
	bool m_Start = false;
	bool m_FadeFinish = false;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetClear(bool IsClear) { m_IsClear = IsClear; }
	void Start() { m_Start = true; }
	bool GetFadeFinish() { return m_FadeFinish; }
};