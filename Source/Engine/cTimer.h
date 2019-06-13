//////////////////////////////////////////////////////////////////////////////////
// Project: SDL Game Engine
//////////////////////////////////////////////////////////////////////////////////

#pragma once

#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL_TTF.lib")

#include "SDL.h" 

class cTimer
{
public:
	cTimer()
	{
		// Tell SDL to intialize its timer component //
		SDL_Init(SDL_INIT_TIMER);

		Reset();	
	}

	~cTimer()
	{
	}

	// Return the number of milliseconds that have passed since Reset() was last called 
	int GetMilliseconds()
	{
		// Take the current time and subtract the time that ResetTicks() was last called //
		return SDL_GetTicks() - m_Ticks;
	}

	// Return the number of seconds that have passed since Reset() was last called 
	int GetSeconds()
	{
		return GetMilliseconds() / 1000;
	}

	// Reset the timer 
	void Reset()
	{
		m_Ticks = SDL_GetTicks();
	}     

private:
	// This variable stores the time the Reset() was 
	// last called at. See GetMilliseconds() for its use. 
	int m_Ticks;	
};

// Aaron Cox, 2005 
