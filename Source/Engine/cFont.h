#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Color.h"
#include "Size.h"

typedef enum FontStyle
{
	FontStyle_Normal = 0,
	FontStyle_Bold = 1,
	FontStyle_Italic = 2,
	FontStyle_Underline = 4
} FontStyle;

class cFont
{
public:
	cFont()
	{
		m_Font = 0;
	}

	cFont(TTF_Font* Font)
	{
		m_Font = Font;
	}

	~cFont(void)
	{
		TTF_CloseFont(m_Font);
	}

public:
	void SetStyle(int Style);
	Size GetSize(std::string Text);

	static cFont* FromFile(std::string FileName, int Size);
	
	__declspec(property(get = GetFont)) TTF_Font* Font;
	TTF_Font* GetFont(void) { return m_Font; }
	
private:
	TTF_Font* m_Font;
};

