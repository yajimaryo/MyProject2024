#pragma once

#include "scene.h"

class Fade;
class Polygon2D;
class Audio;

class Title : public Scene
{
private:
	int m_Cursor = 0;
	D3DXVECTOR2 m_CursorPosition[2]{};

	Polygon2D* m_Polygon = nullptr;

	Audio* m_SelectSE = nullptr;
	Audio* m_OkSE = nullptr;

public:
	void Init() override;
	void Update() override;
};