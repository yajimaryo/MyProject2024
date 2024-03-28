#pragma once

#include "mutantState.h"

class MutantStateSkill : public MutantState
{
private:
	int m_Frame = 0;
	int m_AttackTime = 100;	//全体フレーム
	int m_AttackFrame = 90;	//発生フレーム

public:
	explicit MutantStateSkill(EnemyMutant* pMutant);
	virtual ~MutantStateSkill() {}
	virtual void Update(EnemyMutant* pMutant) override;

private:
	MutantStateSkill() {}
};