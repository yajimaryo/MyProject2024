#pragma once

#include "mutantState.h"

class MutantStateWalk : public MutantState
{
private:
	float m_Speed = 0.01f;
	float m_SpeedMax = 0.1f;

public:
	explicit MutantStateWalk(EnemyMutant* pMutant, float Speed = 0.01f);
	virtual ~MutantStateWalk() {}
	virtual void Update(EnemyMutant* pMutant) override;

private:
	MutantStateWalk() {}
};