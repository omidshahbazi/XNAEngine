#pragma once

#include "Engine\cGame.h"
#include "cState.h"
#include "cMenuButton.h"

class cMenuState :
	public cState
{
public:
	cMenuState(cGame *m_Game);
	~cMenuState(void);

public:
	void HandleInput(void);
	void LoadState(void);

	void Update(cGameTime* GameTime);
	void Draw(cGameTime* GameTime, cSpriteBatch* SpriteBatch);

private:
	cGame *m_Game;
	cFont *m_ButtonFont, *m_TitleFont;
	cTexture *m_Background, *m_BackMessage;
	cTexture *m_BackButton, *m_BackButtonOn;
	cMenuButton *m_NewGameButton, *m_StartGameButton, *m_QuitButton, *m_YesButton, *m_NoButton;
	MouseEvent *m_MouseEvent;
	bool m_QuitSubmitShow;
};
