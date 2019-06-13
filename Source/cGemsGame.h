#pragma once

#include "Engine\cGame.h"
#include "cIntroState.h"
#include "cMenuState.h"
#include "cGameState.h";

class cGemsGame : public cGame
{
public:
	cGemsGame(void);
	~cGemsGame(void);

public:
	void ChangeState(States state);
	void ReloadGameState(void);

private:
	void LoadGame(void);
	void Update(cGameTime* GameTime);
	void Draw(cGameTime* GameTime);

private:
	static const int TargetFrameRate = 42;

	cState *m_StateToRender;

	cIntroState *m_Intro;
	cMenuState *m_Menu;
	cGameState *m_Game;

	cSound *m_BackgroundMusic;
};

