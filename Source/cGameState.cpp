
#include "cGameState.h"
#include "cGemsGame.h"

cGameState::cGameState(cGame *Game) : cState(Game->Content, Game->Input)
{
	m_Game = Game;

	LoadState();
}

cGameState::~cGameState(void)
{
	delete m_HudFont;
	delete m_WinOverlay;
	delete m_LoseOverlay;
	delete m_DiedOverlay;
}

void cGameState::LoadLastState()
{
	std::FILE *file = Content->OpenFileStream(cLevel::SaveFilePath.c_str(), "r");

	int levelIndex = 0;

	if (file != NULL)
	{
		char data[100];

		fgets(data, 100, file);

		levelIndex = atoi(data) + 1;

		fclose(file);
	}

	while (true)
	{
		try
		{
			m_Level = new cLevel(levelIndex, Content, m_Game->AudioEngine, Input);
		}
		catch(...)
		{
			levelIndex = 0;
			m_Level = new cLevel(levelIndex, Content, m_Game->AudioEngine, Input);
		}
        
		break;
	}
}

void cGameState::HandleInput(void)
{
	if (Input->EventOccurs())
	{
		if (Input->QuitOccurs())
		{	
			((cGemsGame*)m_Game)->ChangeState(States_Menu);
		}

		switch (Input->GetPressedKey())
		{
			case SDLK_ESCAPE:
				{
					((cGemsGame*)m_Game)->ChangeState(States_Menu);
				} break;
		}
	}

	m_ContinuePressed = (Input->GetDownedKey() == SDLK_SPACE);

	if (!m_WasContinuePressed && m_ContinuePressed)
	{
		if (!m_Level->Player->IsAlive)
		{
			m_Level->StartNewLife();
		}
		else if (m_Level->TimeRemaining == 0.0f)
		{
			LoadLastState();
		}
	}
}

void cGameState::DrawHud(void)
{
	Vector center = Vector(m_Game->Window->WindowSize.Width / 2.0f,
		m_Game->Window->WindowSize.Height / 2.0f);

    Color timeColor = Color(255, 255, 0);

	int remainSeconds = m_Level->TimeRemaining / 60;

	if (!m_Level->ReachedExit && remainSeconds < 5)
	{
		timeColor.Green = 0;
	}
	
	Vector pos = Vector(5);
	
	std::string st = "Time Remaining : " + IntToString(m_Level->TimeRemaining / 60) + ":" + IntToString(m_Level->TimeRemaining % 60);

	m_Game->SpriteBatch->DrawString(m_HudFont, st, pos, timeColor);

	pos.Y += m_HudFont->GetSize(st).Height;

	m_Game->SpriteBatch->DrawString(m_HudFont, "Score : " + IntToString(m_Level->Score), pos, Color(255, 255, 0));

    cTexture *status = NULL;

	if (m_Level->TimeRemaining == 0.0f)
    {
		if (m_Level->ReachedExit)
        {
            status = m_WinOverlay;
        }
        else
        {
            status = m_LoseOverlay;
        }
    }
	else if (!m_Level->Player->IsAlive)
    {
        status = m_DiedOverlay;
    }

	if (status != NULL)
    {
        // Draw status message.
        Vector statusSize = Vector(status->Width, status->Height);

		m_Game->SpriteBatch->Draw(status, center - statusSize / 2);
    }
}

void cGameState::LoadState(void)
{
	m_WasContinuePressed = false;

	m_HudFont = Content->LoadFont("Fonts\\Tahoma.ttf", 17);
	m_HudFont->SetStyle(FontStyle_Bold);

	m_WinOverlay = Content->LoadTexture("Overlays\\you_win.jpg");
	m_LoseOverlay = Content->LoadTexture("Overlays\\you_lose.jpg");
	m_DiedOverlay = Content->LoadTexture("Overlays\\you_died.jpg");

	LoadLastState();
}

void cGameState::Update(cGameTime* GameTime)
{
	//
	// Update game ligics here
	//

	if (m_Game->Window->ShowCursor)
		m_Game->Window->ShowCursor = false;

	HandleInput();

	m_Level->Update(GameTime);

	cState::Update(GameTime);
}

void cGameState::Draw(cGameTime* GameTime, cSpriteBatch *SpriteBatch)
{
	//
	// Draw anythings here
	//

	m_Level->Draw(GameTime, SpriteBatch);

	DrawHud();

	cState::Draw(GameTime, SpriteBatch);
}