#pragma once

#include "gameObject.h"

#define DIGITS 5

class AnimSprite;
class Audio;

class Score : public GameObject
{
private:
	AnimSprite* m_AS[DIGITS]{};
	Audio* m_AddSE = nullptr;

	int m_Score = 0;
	int m_DrawScore = 0;
	int m_AddNumber = 0;
	bool m_AddEnd = false;
	bool m_IsDraw = true;

public:
	void Init(float x, float y, float Width, float Height, float Space, int AddNumber = 3);
	void Update();
	void Uninit();
	void Draw();

	void AddScore(int Score) { m_Score += Score; }
	void SetScore(int Score) { m_Score = Score; }
	int GetScore() { return m_Score; }

	bool AddEnd() { return m_AddEnd; }
	void SetDraw(bool IsDraw) { m_IsDraw = IsDraw; }
};