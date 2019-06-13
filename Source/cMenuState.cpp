
#include "cMenuState.h"
#include "cGemsGame.h"

cMenuState::cMenuState(cGame *Game) : cState(Game->Content, Game->Input)
{
	m_Game = Game;

	LoadState();
}

cMenuState::~cMenuState(void)
{
}

void cMenuState::HandleInput(void)
{
	if (Input->EventOccurs()) 
	{
		if (Input->QuitOccurs())
		{	
			m_QuitSubmitShow = true;
		}

		switch (Input->GetPressedKey())
		{
			case SDLK_ESCAPE:
				{
					m_QuitSubmitShow = !m_QuitSubmitShow;

				} break;

			case SDLK_RETURN:
				{
					if (m_QuitSubmitShow)
						m_Game->Exit();
					else
						((cGemsGame*)m_Game)->ChangeState(States_Game);

				} break;
		}
	}

	m_MouseEvent = Input->GetMouseEvent();
}

void cMenuState::LoadState(void)
{
	m_QuitSubmitShow = false;

	m_ButtonFont = Content->LoadFont("Fonts\\Tahoma.ttf", 18);
	m_TitleFont = Content->LoadFont("Fonts\\Tahoma.ttf", 27);
	m_TitleFont->SetStyle(FontStyle_Bold);

	m_Background = Content->LoadTexture("UI\\Main.jpg");
	m_BackMessage = Content->LoadTexture("UI\\BackMessage.bmp", Color(0,0,0));

	m_BackButton = Content->LoadTexture("UI\\BackButton.bmp", Color(0,0,0));
	m_BackButtonOn = Content->LoadTexture("UI\\BackButtonOn.bmp", Color(0,0,0));

	m_YesButton = new cMenuButton(m_BackButton, m_Game->Window->WindowCenter - Vector(150, 0), m_ButtonFont, "Yes", Vector(60, 6));
	m_NoButton = new cMenuButton(m_BackButton, m_Game->Window->WindowCenter + Vector(50, 0), m_ButtonFont, "No", Vector(60, 6));

	m_NewGameButton = new cMenuButton(m_BackButton, Vector(35, 240), m_ButtonFont, "New Game", Vector(35, 11));
	m_NewGameButton->Effect->Rotation = -5.0;
	m_NewGameButton->Effect->ZoomX = 1.2f;

	m_StartGameButton = new cMenuButton(m_BackButton, Vector(560, 330), m_ButtonFont, "Start Game", Vector(30, 6));
	m_StartGameButton->Effect->ZoomX = 1.1f;

	m_QuitButton = new cMenuButton(m_BackButton, Vector(1035, 345), m_ButtonFont, "Quit", Vector(60, 11));
	m_QuitButton->Effect->Rotation = 3.0;
	m_QuitButton->Effect->ZoomX = 1.2f;
}

void cMenuState::Update(cGameTime* GameTime)
{
	//
	// Update game ligics here
	//
	
	if (!m_Game->Window->ShowCursor)
		m_Game->Window->ShowCursor = true;

	HandleInput();

	m_YesButton->Texture = m_BackButton;
	m_NoButton->Texture = m_BackButton;
	m_QuitButton->Texture = m_BackButton;
	m_NewGameButton->Texture = m_BackButton;
	m_StartGameButton->Texture = m_BackButton;

	MouseEvent mouseEvent = MouseEvent(MouseButton_None, 0, 0);

	if (m_MouseEvent)
		mouseEvent = *m_MouseEvent;


	if (m_YesButton->BoundingRectangle.Contains(m_Game->MousePosition))
	{
		m_YesButton->Texture = m_BackButtonOn;

		if (mouseEvent.Button == MouseButton_Left)
			m_Game->Exit();
	}

	if (m_NoButton->BoundingRectangle.Contains(m_Game->MousePosition))
	{
		m_NoButton->Texture = m_BackButtonOn;

		if (mouseEvent.Button == MouseButton_Left)
			m_QuitSubmitShow = false;
	}

	if (m_QuitButton->BoundingRectangle.Contains(m_Game->MousePosition))
	{
		m_QuitButton->Texture = m_BackButtonOn;

		if (mouseEvent.Button == MouseButton_Left)
			m_QuitSubmitShow = true;
	}

	if (m_NewGameButton->BoundingRectangle.Contains(m_Game->MousePosition))
	{
		m_NewGameButton->Texture = m_BackButtonOn;

		if (mouseEvent.Button == MouseButton_Left)
		{
			Content->DeleteFile(cLevel::SaveFilePath);

			((cGemsGame*)m_Game)->ReloadGameState();

			((cGemsGame*)m_Game)->ChangeState(States_Game);
		}
	}

	if (m_StartGameButton->BoundingRectangle.Contains(m_Game->MousePosition))
	{
		m_StartGameButton->Texture = m_BackButtonOn;

		if (mouseEvent.Button == MouseButton_Left)
			((cGemsGame*)m_Game)->ChangeState(States_Game);
	}

	cState::Update(GameTime);
}

void cMenuState::Draw(cGameTime* GameTime, cSpriteBatch *SpriteBatch)
{
	//
	// Draw anythings here
	//

	SpriteBatch->Draw(m_Background, Vector());

	SpriteEffects effect = SpriteEffects();
	effect.RotationAround = m_BackButton->Center;
	effect.Rotation = -12.0;
	effect.ZoomX = 3.0f;
	SpriteBatch->Draw(m_BackButton, Vector(230, 130), effect);

	effect.ZoomX = 1.0f;
	SpriteBatch->DrawString(m_TitleFont, "GEMS GAME", Vector(230, 130), Color(0, 0, 0), effect);

	m_NewGameButton->Draw(SpriteBatch);
	m_StartGameButton->Draw(SpriteBatch);
	m_QuitButton->Draw(SpriteBatch);

	if (m_QuitSubmitShow)
	{
		Vector strat =  m_Game->Window->WindowCenter -m_BackMessage->Center;

		SpriteBatch->Draw(m_BackMessage, strat);

		SpriteBatch->DrawString(m_ButtonFont, "Are you sure want to quit the game ?", strat + Vector(100, 100), Color(0, 0, 0));

		m_YesButton->Draw(SpriteBatch);
		m_NoButton->Draw(SpriteBatch);
	}

	cState::Draw(GameTime, SpriteBatch);
}