#pragma once

#include "gameObject.h"

class Sprite;

class Fade : public GameObject
{
private:

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	Sprite* m_Sprite = nullptr;

	float m_Alpha = 0.0f;
	bool m_Out = false;
	bool m_FadeFinish = false;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void FadeOut() { m_Out = true; }
	bool GetFadeFinish() { return m_FadeFinish; }
};