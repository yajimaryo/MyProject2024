#pragma once

#include "enemy.h"
#include <string>

class MutantState;
class AnimationModel;

class EnemyMutant : public Enemy
{
private:
	MutantState* m_MutantPattern = nullptr;

	static AnimationModel* m_Model;
	int m_AnimTime = 0;
	int m_NextAnimTime = 0;
	std::string m_AnimationName;
	std::string m_NextAnimationName;
	float m_AnimBlendRate = 0.0f;

	int m_SkillCT;

public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void ChangeMutantPattern(MutantState* MutantPattern);
	void ChangeAnimation(std::string AnimName);

	int GetSkillCT(void) { return m_SkillCT; }
	void SetSkillCT(void) { m_SkillCT = 600; }
};