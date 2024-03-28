#pragma once


class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];

	static bool m_MouseRButton;
	static bool m_MouseLButton;

public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );

	static bool GetMouseRTrigger();
	static bool GetMouseLTrigger();

	static bool GetMouseRPress(){
		return GetAsyncKeyState(VK_RBUTTON);
	}

	static bool GetMouseLPress() {
		return GetAsyncKeyState(VK_LBUTTON);
	}
};
