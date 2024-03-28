#pragma once

#include "weapon.h"

class Sword : public Weapon
{
public:
	Sword() :Weapon::Weapon(45, 20, 10.0f, -1, 0.0f, 0,(char*)"asset/texture/field004.jpg", (char*)"asset/audio/slash.wav"){}

	void WeaponAttack(D3DXVECTOR3 Position, D3DXVECTOR3 Direction) override;
};