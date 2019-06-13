#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Color.h"
#include "Vector.h"

class cTexture
{
public:
	cTexture()
	{
		cTexture::m_Buffer = 0;
	}

	cTexture(SDL_Surface* Buffer)
	{
		cTexture::m_Buffer = Buffer;
	}

	~cTexture(void)
	{
		//if (m_Buffer)
		//	SDL_FreeSurface(m_Buffer);
	}

public:
	void SetTransparentColor(Color TransparentColor);
	static void SetTransparentColor(SDL_Surface* Surface, Color TransparentColor);
	static cTexture* FromFile(std::string FileName, Color TransparentColor = Color(255, 255, 255));
	
	__declspec(property(get = GetBuffer)) SDL_Surface* Buffer;
	SDL_Surface* GetBuffer(void) { return m_Buffer; }

	__declspec(property(get = GetWidth)) int Width;
	int GetWidth(void) 
	{
		if (m_Buffer)
			return (m_Buffer->clip_rect.w); 
		
		return 0;
	}
	__declspec(property(get = GetHeight)) int Height;
	int GetHeight(void) 
	{
		if (m_Buffer)
			return (m_Buffer->clip_rect.h); 
	
		return 0;
	}

	__declspec(property(get = GetCenter)) Vector Center;
	Vector GetCenter(void) { return Vector(Width / 2.0f, Height / 2.0f); }

private:
	SDL_Surface* m_Buffer;
};

