#pragma once

#include "gameObject.h"

class Camera : public GameObject
{

private:

	D3DXVECTOR3 m_Target;
	D3DXMATRIX m_ViewMatrix;
	D3DXMATRIX m_ProjectionMatrix;

	float m_Up = 2.0f;
	bool m_Peek = false;

	float m_ShakeAmplitude = 0.0f;
	int m_ShakeTime = 0;
	float m_ShakeOffset = 0.0f;

public:
	void Init();
	void Update();
	void Draw();

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }
	bool CheckView(D3DXVECTOR3 Position, D3DXVECTOR3 Size);
	float GetUp(void) { return m_Up; }
	void SetPeek(bool Peek) { m_Peek = Peek; }

	D3DXVECTOR3 GetForward()override
	{
		D3DXMATRIX rot;

		D3DXMatrixInverse(&rot, nullptr, &m_ViewMatrix);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	void Shake(float Amplitude) { m_ShakeAmplitude = Amplitude; }
};