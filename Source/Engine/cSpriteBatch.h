#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include <vector>
#include "Sprite.h"
#include "cTexture.h"
#include "cFont.h"
#include "Rectangle.h"
#include "Vector.h"
#include "Color.h"

class cSpriteBatch
{
public:
	cSpriteBatch(SDL_Surface* BackBuffer);
	~cSpriteBatch(void)
	{
		SDL_FreeSurface(m_BackBuffer);

		TTF_Quit();
	}

public:
	void Clear(Color BackColor = Color(0, 0, 0));

	void Draw(cTexture* Texture, Vector DestinationVector);
	void Draw(cTexture* Texture, Vector DestinationVector, SpriteEffects Effects);
	void Draw(cTexture* Texture, Vector SourceVector, Vector DestinationVector);
	void Draw(cTexture* Texture, Vector SourceVector, Vector DestinationVector, SpriteEffects Effects);
	void Draw(cTexture* Texture, Rectangle SourceRectangle, Vector DestinationVector);
	void Draw(cTexture* Texture, Rectangle SourceRectangle, Vector DestinationVector, SpriteEffects Effects);
	void Draw(cTexture* Texture, Rectangle SourceRectangle, Rectangle DestinationRectangle);
	void Draw(cTexture* Texture, Rectangle SourceRectangle, Rectangle DestinationRectangle, SpriteEffects Effects);

	void Flip(cTexture *&Texture, SpriteEffects Effect);
	SDL_Surface* Flip(SDL_Surface *Surface, SpriteEffects Effect);

	void DrawString(cFont *Font, std::string Text, Vector Position, Color ForeColor);
	void DrawString(cFont *Font, std::string Text, Vector Position, Color ForeColor, SpriteEffects Effects);
	void DrawString(cFont *Font, std::string Text, Vector Position, Color ForeColor, Color BackColor);
	void DrawString(cFont *Font, std::string Text, Vector Position, Color ForeColor, Color BackColor, SpriteEffects Effects);

	void Flush(void);
	
	__declspec(property(get = GetBackColor)) Color BackColor;
	Color GetBackColor(void) { return m_BackColor; }

private:
	static Uint32 GetPixel(SDL_Surface *Surface, int X, int Y);
	static void PutPixel(SDL_Surface *Surface, int X, int Y, Uint32 PixelColor);

	void DrawStringCore(SDL_Surface *temp, Rectangle DestinationRectangle, SpriteEffects Effects);

	void DrawCore(cTexture* Texture, Rectangle SourceRectangle, Rectangle DestinationRectangle, SpriteEffects Effects);

private:
	std::vector<Sprite*> m_SpriteList;
	SDL_Surface *m_BackBuffer;
	Color m_BackColor;
};

