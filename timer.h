#pragma once

#include "gameObject.h"

class Guage;
class AnimSprite;

class Timer : public GameObject
{
private:
	Guage* m_Guage = nullptr;
	AnimSprite* m_Sprite = nullptr;

	int m_TimeLimit = 0;
	int m_TimeNow = 0;

public:
	void Init();
	void Update();
	void Uninit();
	void Draw();

	bool Finish()
	{
		if (m_TimeNow <= 0)
		{
			return true;
		}
		return false;
	}
};