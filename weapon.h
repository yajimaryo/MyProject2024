#pragma once

#include <list>
#include "component.h"
#include "gameObject.h"

class Audio;
class Guage;
class Score;

class Weapon : public GameObject
{
private:
	Audio* m_ReloadSound = nullptr;
	Guage* m_Guage = nullptr;
	bool m_Main = true;
	
protected:
	Audio* m_AttackSound = nullptr;
	
	int m_AttackTime = 0;	//�S�̃t���[��(���˃��[�g)
	int m_AttackFrame = 0;	//�����t���[��
	
	float m_Damage = 0.0f;
	int m_BulletNum = -1;
	int m_BulletMax = -1;
	float m_BulletSpd = 0.0f;

	int m_NowReloadTime = 0;
	int m_ReloadTime = 0;
	bool m_IsReload = false;

	char* m_TextureName = NULL;
	char* m_SoundName = NULL;

	Score* m_BulletCount[2];

	int m_Player = 0; //�Q�[���I�u�W�F�N�g:0.�v���C���[ 1.�G 2,���̑�

public:
	Weapon(int AttackTime,int AttackFrame, float Damage,int BulletNum,float BulletSpd, int ReloadTime, char* TextureName,char* SoundName)
		:m_AttackTime(AttackTime),m_AttackFrame(AttackFrame),m_Damage(Damage),
		m_BulletNum(BulletNum), m_BulletMax(BulletNum), m_BulletSpd(BulletSpd),m_ReloadTime(ReloadTime),
		m_TextureName(TextureName),m_SoundName(SoundName){}

	virtual void Init(int Player);

	void Update() override;
	void Draw() override;

	void Attack(D3DXVECTOR3 Position, D3DXVECTOR3 Direction);

	void Reload();

	bool CanAttack()
	{
		if (m_IsReload)
			return false;

		return true;
	}

	virtual int GetAttackTime() { return m_AttackTime; }
	virtual int GetAttackFrame() { return m_AttackFrame; }

	void SetMain(bool IsMain);

protected:

	virtual void WeaponAttack(D3DXVECTOR3 Position, D3DXVECTOR3 Direction) {}
};