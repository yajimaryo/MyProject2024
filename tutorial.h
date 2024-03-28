#pragma once

#include "scene.h"

class Polygon2D;
class GameClear;
class Player;

class Tutorial : public Scene
{
private:
	static bool m_LoadFinish;
	Polygon2D* m_Polygon = nullptr;
	GameClear* m_GameClear = nullptr;
	Player* m_Player = nullptr;
	bool m_First = true;

public:
	static void Load();
	static void Unload();
	static bool GetLoadFinish() { return m_LoadFinish; }

	void Init() override;
	void Uninit() override;
	void Update() override;

	void SpawnEnemy() override;
};