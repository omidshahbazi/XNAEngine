#include "cTexture.h"

void cTexture::SetTransparentColor(Color TransparentColor)
{
	cTexture::SetTransparentColor(m_Buffer, TransparentColor);
}

void cTexture::SetTransparentColor(SDL_Surface* Surface, Color TransparentColor)
{
	if (Surface)
		SDL_SetColorKey(Surface, SDL_SRCCOLORKEY, SDL_MapRGB(Surface->format, TransparentColor.Red, TransparentColor.Green, TransparentColor.Blue));
}

cTexture* cTexture::FromFile(std::string FileName, Color TransparentColor)
{
	/*cTexture* texture = new cTexture(SDL_LoadBMP(FileName.c_str()));
	
	texture->SetTransparentColor(TransparentColor);
	
	return texture;*/



	SDL_Surface *loadedImage = IMG_Load(FileName.c_str()), 
				*optimizedImage = NULL;
	
	if(loadedImage != NULL)
	{
		//loadedImage = SDL_DisplayFormat(loadedImage); // memory leak!!

		// optimized way is :

		optimizedImage = SDL_DisplayFormat(loadedImage);

		SDL_BlitSurface(loadedImage, NULL, optimizedImage, NULL);

		SDL_FreeSurface(loadedImage);
	}
	else
	{
		loadedImage = 0;
	}

	cTexture* texture = new cTexture(optimizedImage);
	
	texture->SetTransparentColor(TransparentColor);

	return texture;
}