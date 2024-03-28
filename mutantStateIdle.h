#pragma once

#include "mutantState.h"

class MutantStateIdle : public MutantState
{
private:
	int m_CoolTime = 0;

public:
	explicit MutantStateIdle(EnemyMutant* pMutant,int CoolTime = 0);
	virtual ~MutantStateIdle() {}
	virtual void Update(EnemyMutant* pMutant) override;

private:
	MutantStateIdle() {}
};