#include "cGameWindow.h"

SDL_Surface* cGameWindow::CreateWindow(void)
{
	return cGameWindow::CreateWindow(false, false);
}

SDL_Surface* cGameWindow::CreateWindow(bool FullScreen)
{
	return cGameWindow::CreateWindow(FullScreen, false);
}

SDL_Surface* cGameWindow::CreateWindow(bool FullScreen, bool DoubleBuffer)
{
	int flags = 0;

	flags |= SDL_ANYFORMAT;

	//flags |= SDL_SWSURFACE;

	if (FullScreen)
	{
		flags |= SDL_FULLSCREEN;
		
		if (m_GetScreenSize)
		{
			const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();

			m_width = videoInfo->current_w;
			m_height = videoInfo->current_h;
		}
	}

	if (DoubleBuffer)
		flags |= SDL_DOUBLEBUF;

	m_BackBuffer = SDL_SetVideoMode(m_width, m_height, 32, flags);

	SetCaption(m_Caption);
	
	return m_BackBuffer;
}

void cGameWindow::SetCaption(std::string Caption)
{
	m_Caption = Caption;
	
	SDL_WM_SetCaption(("Aban Engine - " + m_Caption).c_str(), 0);
}

void cGameWindow::SetIcon(std::string FileName)
{
	SetIcon(IMG_Load(FileName.c_str()));
}

void cGameWindow::SetIcon(SDL_Surface *Icon)
{
	SDL_WM_SetIcon(Icon, NULL);
}