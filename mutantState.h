#pragma once

class EnemyMutant;

class MutantState
{
public:
	virtual ~MutantState() {}
	virtual void Update(EnemyMutant* pMutant) = 0;
};