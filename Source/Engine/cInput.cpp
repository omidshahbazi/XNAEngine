#include "cInput.h"

cInput::cInput(void)
{
	for (int i=0; i<323; i++)
	{
		m_KeysHeld[i] = false;
	}
}

cInput::~cInput(void) {}

bool cInput::EventOccurs()
{
	bool result = SDL_PollEvent(&m_Event);

	// Fill the event structure with event information //
	if (result)
	{
		// Tell m_KeysHeld that a key has been pressed //
		if (m_Event.type == SDL_KEYDOWN)
		{
			m_KeysHeld[m_Event.key.keysym.sym] = true;
		}
		// Tell m_KeysHeld that a key has been released //
		if (m_Event.type == SDL_KEYUP)
		{
			m_KeysHeld[m_Event.key.keysym.sym] = false;
		}
	}
	
	return result;
}

// Return true if user has manually closed the window //
bool cInput::QuitOccurs()
{
	if (m_Event.type == SDL_QUIT)
		return true;

	return false;
}

// If a key has been pressed, return its SDL key code. Return -1 if no key was pressed. //
int cInput::GetDownedKey(void)
{
	if (m_Event.type == SDL_KEYDOWN)
	{
		return m_Event.key.keysym.sym;
	}

	return -1;
}

// If a key has been pressed, return its SDL key code. Return -1 if no key was pressed. //
int cInput::GetPressedKey()
{
	//if (m_Event.type == SDL_KEYDOWN)
	//{
	//	return m_Event.key.keysym.sym;
	//}
	if (m_Event.type == SDL_KEYUP)
	{
		return m_Event.key.keysym.sym;
	}
	//if(m_Event.type == SDL_MOUSEMOTION)
	//{
	//	return 0;
	//}

	return -1;
}


// Return true if the given key is being held down //
bool cInput::IsKeyHeld(int key)
{
	return m_KeysHeld[key];
}


MouseEvent* cInput::GetMouseEvent()
{
	MouseEvent *mouseEvent = NULL;
	
	if(m_Event.type == SDL_MOUSEBUTTONUP)
	{
		switch (m_Event.button.button)
		{
		case MouseButton_Left:
			{
				mouseEvent = new MouseEvent(MouseButton_Left, m_Event.button.x, m_Event.button.y);
			} break;
		case MouseButton_Middle:
			{
				mouseEvent = new MouseEvent(MouseButton_Middle, m_Event.button.x, m_Event.button.y);
			} break;
		case MouseButton_Right:
			{
				mouseEvent = new MouseEvent(MouseButton_Right, m_Event.button.x, m_Event.button.y);
			} break;
		}
	}

	return mouseEvent;
}

//MouseEvent* cInput::GetMouseMove()
//{
//	MouseEvent *mouseEvent = NULL;
//	
//	if(m_Event.type == SDL_MOUSEMOTION)
//	{
//		mouseEvent = new MouseEvent(MouseButton_None, m_Event.motion.x, m_Event.motion.y, m_Event.motion.xrel, m_Event.motion.yrel);
//	}
//
//	return mouseEvent;
//}