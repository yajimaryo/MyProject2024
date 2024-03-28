#pragma once

#include "scene.h"

class Score;

class Result : public Scene
{
private:
	static int m_Score;
	static int m_Hp;

	Score* m_Scores[4]{};

public:
	void Init() override;
	void Update() override;

	static void SetScore(int Score) { m_Score = Score; }
	static void SetHp(int Hp) { m_Hp = Hp; }
};