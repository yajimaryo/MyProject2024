#pragma once

#include "mutantState.h"

class MutantStateAttack : public MutantState
{
private:
	int m_Frame = 0;
	int m_AttackTime = 60;	//�S�̃t���[��
	int m_AttackFrame = 30;	//�����t���[��

public:
	explicit MutantStateAttack(EnemyMutant* pMutant);
	virtual ~MutantStateAttack() {}
	virtual void Update(EnemyMutant* pMutant) override;

private:
	MutantStateAttack() {}
};