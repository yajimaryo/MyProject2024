#pragma once

#include "scene.h"

class Polygon2D;
class GameClear;
class Player;

class Stage : public Scene
{
private:
	static bool m_LoadFinish;
	GameClear* m_GameClear = nullptr;
	Player* m_Player = nullptr;

public:
	static void Load();
	static void Unload();
	static bool GetLoadFinish() { return m_LoadFinish; }

	void Init() override;
	void Uninit() override;
	void Update() override;

	void SpawnEnemy() override;
};