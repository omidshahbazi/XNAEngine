#pragma once

#include "Engine\cGame.h"
#include "cState.h"
#include "cLevel.h"

class cGameState : public cState
{
public:
	cGameState(cGame *Game);
	~cGameState(void);

public:
	void HandleInput(void);
	void LoadState(void);
	void DrawHud(void);

	void Update(cGameTime* GameTime);
	void Draw(cGameTime* GameTime, cSpriteBatch* SpriteBatch);

private:
	void LoadLastState(void);

private:
	cGame *m_Game;
	cLevel *m_Level;
	cFont *m_HudFont;

	cTexture *m_WinOverlay, *m_LoseOverlay, *m_DiedOverlay;

	bool m_ContinuePressed, m_WasContinuePressed;
};
