#pragma once

#include "weapon.h"

class Launcher : public Weapon
{
public:
	Launcher() :Weapon::Weapon(70, 1, 30.0f, 3, 1.5f, 400, (char*)"asset/texture/launcher.png", (char*)"asset/audio/shot.wav") {}

private:
	void WeaponAttack(D3DXVECTOR3 Position, D3DXVECTOR3 Direction) override;
};