#pragma once

#include "Engine\cGame.h"
#include "cState.h"

class cIntroState :
	public cState
{
public:
	cIntroState(cGame *Game);
	~cIntroState(void);

public:
	void LoadState(void);
	void Update(cGameTime *GameTime);
	void Draw(cGameTime *GameTime, cSpriteBatch *SpriteBatch);

private:
	cGame *m_Game;
	SpriteEffects m_Effect;
	cTexture *m_Logo;
};