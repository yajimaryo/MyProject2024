#include "main.h"
#include "enemyMutant.h"
#include "mutantStateWalk.h"
#include "mutantStateIdle.h"

MutantStateIdle::MutantStateIdle(EnemyMutant * pMutant,int CoolTime)
{
	pMutant->ChangeAnimation("Idle");
	m_CoolTime = CoolTime;
}

void MutantStateIdle::Update(EnemyMutant * pMutant)
{
	if (m_CoolTime <= 0)
	{
		if (pMutant->PlayerDist() < 50.0f || pMutant->GetIsFight())
			pMutant->ChangeMutantPattern(new MutantStateWalk(pMutant));
	}
	m_CoolTime--;
}
