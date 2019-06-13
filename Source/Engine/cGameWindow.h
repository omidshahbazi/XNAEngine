
#pragma once

#include <string>
#include <SDL.h>
#include <SDL_Image.h>
#include "Size.h"
#include "Vector.h"

class cGameWindow
{
public:
	cGameWindow() :
		m_width(640),
		m_height(480),
		m_Caption("Game")
	{
		m_GetScreenSize = true;
	}
		
	cGameWindow(int Width, int Height) :
		m_width(Width),
		m_height(Height),
		m_Caption("Game")
	{
		m_GetScreenSize = false;
	}

	cGameWindow(std::string Caption) :
		m_width(640),
		m_height(480),
		m_Caption(Caption)
	{
		m_GetScreenSize = true;
	}

	cGameWindow(int Width, int Height, std::string Caption) :
		m_width(Width),
		m_height(Height),
		m_Caption(Caption)
	{
		m_GetScreenSize = false;
	}

	~cGameWindow(void)
	{
		delete m_BackBuffer;
	}

public:
	__declspec(property(get = GetWindowSize)) Size WindowSize;
	Size GetWindowSize(void) { return Size(m_BackBuffer->clip_rect.w, m_BackBuffer->clip_rect.h); }

	__declspec(property(get = GetWindowCenter)) Vector WindowCenter;
	Vector GetWindowCenter(void) 
	{
		Size sz = WindowSize;

		return Vector(sz.Width / 2.0f, sz.Height / 2.0f); 
	}
	
	__declspec(property(get = GetShowCursor, put = SetShowCursor)) bool ShowCursor;
	bool GetShowCursor(void) { return (SDL_ShowCursor(-1) == 1 ? true : false); }
	void SetShowCursor(bool Value) { SDL_ShowCursor((int)Value); }

	SDL_Surface* CreateWindow(void);
	SDL_Surface* CreateWindow(bool FullScreen);
	SDL_Surface* CreateWindow(bool FullScreen, bool DoubleBuffer);

	void SetCaption(std::string Caption);
	void SetIcon(std::string FileName);
	void SetIcon(SDL_Surface *Icon);

private:
	bool m_GetScreenSize;
	int m_width;
	int m_height;
	std::string m_Caption;

	SDL_Surface* m_BackBuffer;
};

