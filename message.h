#pragma once

#include "gameObject.h"

class AnimSprite;

class Message : public GameObject
{
private:
	AnimSprite* m_Sprite = nullptr;
	bool m_Draw = false;
	float m_Range = 0.0f;
public:
	void Init(float x, float y, float Width, float Height ,char* TextureName);
	void Uninit();
	void Update();
	void Draw();
};