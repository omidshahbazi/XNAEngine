#include "cSpriteBatch.h"

cSpriteBatch::cSpriteBatch(SDL_Surface* BackBuffer)
{
	m_BackBuffer = BackBuffer;
}

void cSpriteBatch::Clear(Color BackColor)
{
	m_BackColor = BackColor;

	SDL_FillRect(m_BackBuffer, NULL, SDL_MapRGB(m_BackBuffer->format, m_BackColor.Red, m_BackColor.Green, m_BackColor.Blue));
}

void cSpriteBatch::Flip(cTexture *&Texture, SpriteEffects Effect)
{
	Texture = new cTexture(Flip(Texture->Buffer, Effect));
}

SDL_Surface* cSpriteBatch::Flip(SDL_Surface *Surface, SpriteEffects Effect)
{	
	if (Effect.Flip != SpriteFlip_None)
	{
		SDL_Surface* flipped_image = NULL;

		// If the image is color keyed 
		if (Surface->flags & SDL_SRCCOLORKEY)
		{
			flipped_image = SDL_CreateRGBSurface(SDL_SWSURFACE, Surface->w, Surface->h, 
					Surface->format->BitsPerPixel, 
					Surface->format->Rmask, 
					Surface->format->Gmask, 
					Surface->format->Bmask, 
					0);
		}
		// Otherwise 
		else
		{
			flipped_image = SDL_CreateRGBSurface(SDL_SWSURFACE, Surface->w, Surface->h, 
					Surface->format->BitsPerPixel, 
					Surface->format->Rmask, 
					Surface->format->Gmask, 
					Surface->format->Bmask, 
					Surface->format->Amask);
		}

		// Lock surface
		if(SDL_MUSTLOCK(Surface))
		{
			SDL_LockSurface(Surface);
		}

		// Go through rows 
		for (int y = 0, ry = Surface->h - 1; y < Surface->h; y++, ry--)
		{
			// Go through columns 
			for (int x = 0, rx = Surface->w - 1; x < Surface->w; x++, rx--)
			{ 
				// Get pixel 
				Uint32 pixel = GetPixel(Surface, x, y); 

				// Copy pixel 
				if(Effect.Flip == SpriteFlip_FlipVertically && Effect.Flip == SpriteFlip_FlipHorizontally)
				{
					PutPixel(flipped_image, rx, ry, pixel);
				}
				else if(Effect.Flip == SpriteFlip_FlipHorizontally)
				{
					PutPixel(flipped_image, rx, y, pixel);
				}
				else if(Effect.Flip == SpriteFlip_FlipVertically)
				{
					PutPixel(flipped_image, x, ry, pixel);
				}
			}
		}

		// Unlock surface
		if(SDL_MUSTLOCK(Surface))
		{
			SDL_UnlockSurface(Surface);
		}

		return flipped_image;
	}

	return Surface;
}

Uint32 cSpriteBatch::GetPixel(SDL_Surface *Surface, int X, int Y)
{
	Uint32 *pixels = (Uint32 *)Surface->pixels;
	
	return pixels[(Y * Surface->w) + X];
} 

void cSpriteBatch::PutPixel(SDL_Surface *Surface, int X, int Y, Uint32 PixelColor)
{
	// Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)Surface->pixels;

    // Set the pixel
    pixels[(Y * Surface->w) + X] = PixelColor;
}

void cSpriteBatch::Draw(cTexture* Texture, Vector DestinationVector)
{
	Draw(Texture, DestinationVector, SpriteEffects());
}

void cSpriteBatch::Draw(cTexture* Texture, Vector DestinationVector, SpriteEffects Effects)
{
	Draw(Texture, Vector(), DestinationVector, Effects);
}

void cSpriteBatch::Draw(cTexture* Texture, Vector SourceVector, Vector DestinationVector)
{
	Draw(Texture, SourceVector, DestinationVector, SpriteEffects());
}

void cSpriteBatch::Draw(cTexture* Texture, Vector SourceVector, Vector DestinationVector, SpriteEffects Effects)
{
	Rectangle rect = Rectangle(SourceVector, Vector(Texture->Buffer->w, Texture->Buffer->h));

	Draw(Texture, rect, DestinationVector, Effects);
}

void cSpriteBatch::Draw(cTexture* Texture, Rectangle SourceRectangle, Vector DestinationVector)
{
	Draw(Texture, SourceRectangle, DestinationVector, SpriteEffects());
}

void cSpriteBatch::Draw(cTexture* Texture, Rectangle SourceRectangle, Vector DestinationVector, SpriteEffects Effects)
{
	Rectangle rect = Rectangle(DestinationVector, Vector(SourceRectangle.Width, SourceRectangle.Height));

	Draw(Texture, SourceRectangle, rect, Effects);
}

void cSpriteBatch::Draw(cTexture* Texture, Rectangle SourceRectangle, Rectangle DestinationRectangle)
{
	Draw(Texture, SourceRectangle, DestinationRectangle, SpriteEffects());
}

void cSpriteBatch::Draw(cTexture* Texture, Rectangle SourceRectangle, Rectangle DestinationRectangle, SpriteEffects Effects)
{
	DrawCore(Texture, SourceRectangle, DestinationRectangle, Effects);
}

void cSpriteBatch::DrawCore(cTexture* Texture, Rectangle SourceRectangle, Rectangle DestinationRectangle, SpriteEffects Effects)
{
	m_SpriteList.push_back(new Sprite(Texture, SourceRectangle, DestinationRectangle, Effects));
}

void cSpriteBatch::DrawString(cFont *Font, std::string Text, Vector Position, Color ForeColor)
{
	DrawString(Font, Text, Position, ForeColor, SpriteEffects());
}

void cSpriteBatch::DrawString(cFont *Font, std::string Text, Vector Position, Color ForeColor, SpriteEffects Effects)
{
	if (Font && !Text.empty())
	{
		SDL_Color fore = { ForeColor.Red, ForeColor.Green, ForeColor.Blue };  // text color

		SDL_Surface* temp = TTF_RenderText_Blended(Font->Font, Text.c_str(), fore);

		// Destroy the font variable
		//TTF_CloseFont(Font->Font);

		DrawStringCore(temp, Rectangle(Position, Vector()), Effects);
	}
}

void cSpriteBatch::DrawString(cFont *Font, std::string Text, Vector Position, Color ForeColor, Color BackColor)
{
	DrawString(Font, Text, Position, ForeColor, BackColor, SpriteEffects());
}

void cSpriteBatch::DrawString(cFont *Font, std::string Text, Vector Position, Color ForeColor, Color BackColor, SpriteEffects Effects)
{
	if (Font && !Text.empty())
	{
		SDL_Color fore = { ForeColor.Red, ForeColor.Green, ForeColor.Blue };  // text color
		SDL_Color back = { BackColor.Red, BackColor.Green, BackColor.Blue };  // color of what's behind the text

		// This renders the text to a temporary surface. There are more text 
		// functions than TTF_RenderText_Shaded(), but this one looks nice.  
		SDL_Surface* temp = TTF_RenderText_Shaded(Font->Font, Text.c_str(), fore, back);

		// Destroy the font variable 
		//TTF_CloseFont(Font->Font);

		DrawStringCore(temp, Rectangle(Position, Vector()), Effects);
	}
}

void cSpriteBatch::DrawStringCore(SDL_Surface *temp, Rectangle DestinationRectangle, SpriteEffects Effects)
{
	m_SpriteList.push_back(new Sprite(new cTexture(temp), DestinationRectangle, Effects));
}

void cSpriteBatch::Flush()
{
	if (m_SpriteList.size())
	{
		SDL_Surface *temp;

		for (int i = 0; i < m_SpriteList.size(); i++)
		{
			Sprite *sprite = m_SpriteList[i];

			SDL_Rect destination;
			
			if (sprite->SourceRectangle.Width > 0 && sprite->SourceRectangle.Height > 0)
			{
				destination.x = sprite->DestinationRectangle.X - (sprite->Effect.Origin.X * (float)sprite->DestinationRectangle.Width / (float)sprite->SourceRectangle.Width);
				destination.y = sprite->DestinationRectangle.Y - (sprite->Effect.Origin.Y * (float)sprite->DestinationRectangle.Height / (float)sprite->SourceRectangle.Height);
				destination.w = sprite->DestinationRectangle.Width;
				destination.h = sprite->DestinationRectangle.Height;
			}
			else
			{
				destination.x = sprite->DestinationRectangle.X - sprite->Effect.Origin.X;
				destination.y = sprite->DestinationRectangle.Y - sprite->Effect.Origin.X;
				destination.w = sprite->DestinationRectangle.Width;
				destination.h = sprite->DestinationRectangle.Height;
			}

			SDL_Rect source = { sprite->SourceRectangle.X, sprite->SourceRectangle.Y, sprite->SourceRectangle.Width, sprite->SourceRectangle.Height };

			// Use ColerKey
			if(sprite->Texture->Buffer->flags & SDL_SRCCOLORKEY)
			{
				temp = SDL_CreateRGBSurface(SDL_SWSURFACE, sprite->SourceRectangle.Width, sprite->SourceRectangle.Height, 
						sprite->Texture->Buffer->format->BitsPerPixel, 
						sprite->Texture->Buffer->format->Rmask, 
						sprite->Texture->Buffer->format->Gmask, 
						sprite->Texture->Buffer->format->Bmask, 
						0);
			}
			// Otherwise
			else
			{
				if (sprite->SurfaceType == SpriteType_Text)
				{
					temp = sprite->Texture->Buffer;
				}
				else if (sprite->SurfaceType == SpriteType_Texture)
				{
					temp = SDL_CreateRGBSurface(SDL_SWSURFACE, sprite->SourceRectangle.Width, sprite->SourceRectangle.Height, 
							sprite->Texture->Buffer->format->BitsPerPixel, 
							sprite->Texture->Buffer->format->Rmask, 
							sprite->Texture->Buffer->format->Gmask, 
							sprite->Texture->Buffer->format->Bmask, 
							sprite->Texture->Buffer->format->Amask);
				}
			}

			SDL_BlitSurface(sprite->Texture->Buffer, &source, temp, NULL);

			temp = Flip(temp, sprite->Effect);

			if (sprite->Texture->Buffer->flags & SDL_SRCCOLORKEY)
			{
				SDL_SetColorKey(temp, SDL_SRCCOLORKEY, sprite->Texture->Buffer->format->colorkey);
			}

			float coefficientX = (float)temp->w,
				coefficientY = (float)temp->h;
			
			SDL_Surface *newTemp = NULL;
			if (sprite->Effect.Rotation != 0.0f || sprite->Effect.ZoomX != 1.0f || sprite->Effect.ZoomY != 1.0f)
				newTemp = rotozoomSurfaceXY(temp, sprite->Effect.Rotation, sprite->Effect.ZoomX, sprite->Effect.ZoomY, sprite->Effect.Smooth);
			else
				newTemp = temp;
			
			coefficientX = newTemp->w / coefficientX;
			coefficientY = newTemp->h / coefficientY;

			destination.x -= sprite->Effect.RotationAround.X * coefficientX;
			destination.y -= sprite->Effect.RotationAround.Y * coefficientY;

			SDL_BlitSurface(newTemp, NULL, m_BackBuffer, &destination);

			SDL_FreeSurface(newTemp);
			
			// Bellow occurs error : Access violation reading location!
			//delete newTemp; 
		}		
		
		//SDL_FreeSurface(temp);
		//delete temp;

		m_SpriteList.clear();

		SDL_UpdateRect(m_BackBuffer, 0, 0, 0, 0);
		
		SDL_FreeSurface(m_BackBuffer);
	}
}