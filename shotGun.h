#pragma once

#include "weapon.h"

class ShotGun : public Weapon
{
public:
	ShotGun() :Weapon::Weapon(45, 6, 5.0f, 10, 1.9f, 300, (char*)"asset/texture/shotgun.png", (char*)"asset/audio/shot.wav") {}

private:
	void WeaponAttack(D3DXVECTOR3 Position, D3DXVECTOR3 Direction) override;
};