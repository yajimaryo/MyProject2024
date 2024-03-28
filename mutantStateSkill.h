#pragma once

#include "mutantState.h"

class MutantStateSkill : public MutantState
{
private:
	int m_Frame = 0;
	int m_AttackTime = 100;	//�S�̃t���[��
	int m_AttackFrame = 90;	//�����t���[��

public:
	explicit MutantStateSkill(EnemyMutant* pMutant);
	virtual ~MutantStateSkill() {}
	virtual void Update(EnemyMutant* pMutant) override;

private:
	MutantStateSkill() {}
};