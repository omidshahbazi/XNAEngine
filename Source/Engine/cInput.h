//////////////////////////////////////////////////////////////////////////////////
// Project: SDL Game Engine
// - NOTE use GetKeyPressed() for key pressed and KeyHeld() for keys being held down
//////////////////////////////////////////////////////////////////////////////////

#pragma once

#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL_TTF.lib")

#include "SDL.h"
#include "Vector.h"

typedef enum MouseButton{
       MouseButton_None = 0,
       MouseButton_Left = 1,
       MouseButton_Middle = 2,
       MouseButton_Right = 3
} MouseButton;

struct MouseEvent
{
public:
	MouseEvent(MouseButton Button, int Y, int X) :
		m_Button(Button),
		m_X(X),
		m_Y(Y)
	{}

	MouseEvent(MouseButton Button, int X, int Y, int XRel, int YRel) :
		m_Button(Button),
		m_X(X),
		m_Y(Y),
		m_XRel(XRel),
		m_YRel(YRel)
	{}

public:
	__declspec(property(get = GetButton)) MouseButton Button;
	MouseButton GetButton(void) { return m_Button; }

	__declspec(property(get = GetLocation)) Vector Location;
	Vector GetLocation(void) { return Vector((float)m_X, (float)m_Y); }

	__declspec(property(get = GetRelLocation)) Vector RelLocation;
	Vector GetRelLocation(void) { return Vector((float)m_XRel, (float)m_YRel); }

private:
	MouseButton m_Button; 
	int m_X, m_Y;
	int m_XRel, m_YRel;
};

class cInput
{
public:
	cInput();
	~cInput();
	
public:
	// Return true if user has manually closed the window
	bool QuitOccurs(void);

	int GetDownedKey(void);

	// Return the SDL key code of the key that's been pressed (see below for SDL key codes)
	int GetPressedKey(void);

	// Return true if the given key is being held down
	bool IsKeyHeld(int key);

	MouseEvent* GetMouseEvent(void);
	//MouseEvent* GetPressedMouseButton(void);
	//MouseEvent* GetMouseMove(void);

	// Fill m_Event and m_KeysHeld with any event information, return false if no event
	bool EventOccurs(void); 

protected:
	SDL_Event m_Event;
	bool m_KeysHeld[323];
};


// SDL Key Code List //
/*
// Numbers //
SDLK_0			
SDLK_1			
SDLK_2			
SDLK_3			
SDLK_4			
SDLK_5			
SDLK_6			
SDLK_7			
SDLK_8			
SDLK_9			
		
// Letters //
SDLK_a			
SDLK_b			
SDLK_c			
SDLK_d			
SDLK_e			
SDLK_f			
SDLK_g			
SDLK_h			
SDLK_i			
SDLK_j			
SDLK_k			
SDLK_l			
SDLK_m			
SDLK_n			
SDLK_o			
SDLK_p			
SDLK_q			
SDLK_r			
SDLK_s			
SDLK_t			
SDLK_u			
SDLK_v			
SDLK_w			
SDLK_x			
SDLK_y			
SDLK_z			

// Numpad Keys //
SDLK_KP0		
SDLK_KP1		
SDLK_KP2		
SDLK_KP3		
SDLK_KP4		
SDLK_KP5		
SDLK_KP6		
SDLK_KP7		
SDLK_KP8		
SDLK_KP9		
SDLK_KP_PERIOD		
SDLK_KP_DIVIDE		
SDLK_KP_MULTIPLY	
SDLK_KP_MINUS		
SDLK_KP_PLUS		
SDLK_KP_ENTER		
SDLK_KP_EQUALS		

// Arrow Keys //
SDLK_UP		
SDLK_DOWN		
SDLK_RIGHT	
SDLK_LEFT		

// Function Keys //
SDLK_F1			
SDLK_F2			
SDLK_F3			
SDLK_F4			
SDLK_F5			
SDLK_F6			
SDLK_F7			
SDLK_F8			
SDLK_F9			
SDLK_F10		
SDLK_F11		
SDLK_F12		
SDLK_F13		
SDLK_F14		
SDLK_F15		
	
// Miscellaneous //
SDLK_INSERT	
SDLK_HOME		
SDLK_END	
SDLK_PAGEUP		
SDLK_PAGEDOWN
SDLK_NUMLOCK	
SDLK_CAPSLOCK	
SDLK_SCROLLOCK	
SDLK_RSHIFT		
SDLK_LSHIFT		
SDLK_RCTRL
SDLK_LCTRL		
SDLK_RALT	
SDLK_LALT		
SDLK_HELP	
SDLK_BREAK	
SDLK_UNDO	
SDLK_LEFTBRACKET
SDLK_BACKSLASH		
SDLK_RIGHTBRACKET	
SDLK_CARET		
SDLK_UNDERSCORE		
SDLK_BACKQUOTE	
SDLK_DELETE	
SDLK_COLON		
SDLK_SEMICOLON		
SDLK_LESS		
SDLK_EQUALS		
SDLK_GREATER	
SDLK_QUESTION		
SDLK_AT	
SDLK_BACKSPACE		
SDLK_TAB		
SDLK_CLEAR		
SDLK_RETURN		
SDLK_PAUSE		
SDLK_ESCAPE		
SDLK_SPACE		
SDLK_EXCLAIM		
SDLK_QUOTEDBL		
SDLK_HASH		
SDLK_DOLLAR		
SDLK_AMPERSAND		
SDLK_QUOTE		
SDLK_LEFTPAREN		
SDLK_RIGHTPAREN		
SDLK_ASTERISK		
SDLK_PLUS		
SDLK_COMMA		
SDLK_MINUS		
SDLK_PERIOD		
SDLK_SLASH		
*/