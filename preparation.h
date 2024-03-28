#pragma once

#include "scene.h"

class Fade;
class Polygon2D;
class Audio;
class WeaponSet;
class StageSelect;

class Preparation : public Scene
{
private:
	int m_Cursor = 0;
	D3DXVECTOR2 m_CursorPosition[3]{};
	bool m_Select = false;
	bool m_Start = false;

	Polygon2D* m_Polygon = nullptr;
	WeaponSet* m_WS = nullptr;
	StageSelect* m_StageSelect = nullptr;

	Audio* m_SelectSE = nullptr;
	Audio* m_OkSE = nullptr;

	GameObject* m_WeaponSprite[6] = {};

public:
	void Init() override;
	void Update() override;

	void SelectRelease() { m_Select = false; }
};