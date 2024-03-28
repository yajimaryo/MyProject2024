
#include "main.h"
#include "input.h"

BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];

bool Input::m_MouseRButton = false;
bool Input::m_MouseLButton = false;


void Input::Init()
{
	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );
	
}

void Input::Uninit()
{


}

void Input::Update()
{

	memcpy( m_OldKeyState, m_KeyState, 256 );

	GetKeyboardState( m_KeyState );

	if (m_MouseRButton == true)
	{
		if (!GetAsyncKeyState(VK_RBUTTON))
			m_MouseRButton = false;
	}
	if (m_MouseLButton == true)
	{
		if (!GetAsyncKeyState(VK_LBUTTON))
			m_MouseLButton = false;
	}
}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

bool Input::GetMouseRTrigger()
{
	if (m_MouseRButton == false)
	{
		if (GetAsyncKeyState(VK_RBUTTON))
		{
			m_MouseRButton = true;
			return true;
		}
	}
	return false;
}

bool Input::GetMouseLTrigger()
{
	if (m_MouseLButton == false)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_MouseLButton = true;
			return true;
		}
	}
	return false;
}


