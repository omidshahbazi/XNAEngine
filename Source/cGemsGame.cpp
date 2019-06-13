#include "cGemsGame.h"
#include "Engine\cAudio.h"


cGemsGame::cGemsGame(void)
	: cGame(true, true, true)
{
	Window->SetIcon("Data\\Icon.bmp");

	TargetElapsedTime = 1000.0f / TargetFrameRate;
	
	Content->RootPath = "Data\\";
}

cGemsGame::~cGemsGame(void)
{
}

void cGemsGame::ChangeState(States state)
{
	switch (state)
	{
	case States_Intro:
		{
			m_StateToRender = m_Intro;
			m_BackgroundMusic->Pause();
		} break;

	case States_Menu:
		{
			m_StateToRender = m_Menu;
			m_BackgroundMusic->Resume();
		} break;

	case States_Game:
		{
			m_StateToRender = m_Game;
			m_BackgroundMusic->Resume();
		} break;
	}
}

void cGemsGame::ReloadGameState()
{
	m_Game = new cGameState(this);
}

void cGemsGame::LoadGame(void)
{
	m_Intro = new cIntroState(this);
	m_Menu = new cMenuState(this);
	ReloadGameState();

	Content->RootPath = "Data\\";

	m_BackgroundMusic = AudioEngine->FromFile("Data\\Sounds\\Music.ogg", true);

	ChangeState(States_Menu);
}

void cGemsGame::Update(cGameTime* GameTime)
{
	if (!GameTime->IsRunningSlowly)
	{
		m_StateToRender->Update(GameTime);

		cGame::Update(GameTime);
	}
}

void cGemsGame::Draw(cGameTime* GameTime)
{
	SpriteBatch->Clear();

	if (!GameTime->IsRunningSlowly)
	{
		m_StateToRender->Draw(GameTime, SpriteBatch);

		cGame::Draw(GameTime);
	}
}
