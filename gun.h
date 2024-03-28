#pragma once

#include "weapon.h"

class Gun : public Weapon
{
public:
	Gun() :Weapon::Weapon(3, 1, 2.0f, 120, 3.0f, 180,(char*)"asset/texture/assault.png", (char*)"asset/audio/shot.wav") {}

private:
	void WeaponAttack(D3DXVECTOR3 Position, D3DXVECTOR3 Direction) override;
};