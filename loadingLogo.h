#pragma once

#include "gameObject.h"


class Sprite;

class LoadingLogo : public GameObject
{
private:

	Sprite* m_Logo = nullptr;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};