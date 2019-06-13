
#include "cIntroState.h"
#include "cGemsGame.h"

cIntroState::cIntroState(cGame *Game) : cState(Game->Content, Game->Input)
{
	m_Game = Game;

	LoadState();
}

cIntroState::~cIntroState(void)
{
}

void cIntroState::LoadState(void)
{
	m_Logo = Content->LoadTexture("UI\\Logo.bmp", Color());

	m_Effect = SpriteEffects();
	m_Effect.RotationAround = Vector(m_Logo->Center.X, m_Logo->Center.Y);
}

void cIntroState::Update(cGameTime *GameTime)
{
	//
	// Update logics here
	//

	if (m_Game->Window->ShowCursor)
		m_Game->Window->ShowCursor = false;

	Input->EventOccurs();

	static cTimer *timer = new cTimer();

	if(timer->GetSeconds() > 0)
		((cGemsGame*)m_Game)->ChangeState(States_Menu);
	else
		m_Effect.Rotation += 1;

	cState::Update(GameTime);
}

void cIntroState::Draw(cGameTime *GameTime, cSpriteBatch *SpriteBatch)
{
	//
	// Draw everything here
	//

	SpriteBatch->Draw(m_Logo, Vector(200), m_Effect);

	cState::Draw(GameTime, SpriteBatch);
}