#include "cGame.h"

void cGame::Initialize(bool InitializeVideo, bool InitializeAudio, bool InitilizeContentManager)
{
	int flags = 0;

	if (InitializeVideo)
		flags |= SDL_INIT_VIDEO;

	// Tell SDL to intialize its components
	SDL_Init(flags);

	//IMG_Init(IMG_INIT_PNG);

	if (InitializeAudio)
		m_AudioEngine = new cAudio();

	if (InitilizeContentManager)
		m_Content = new cContentManager();
}

void cGame::RunCore()
{
	LoadGame();

	m_GameIsRun = true;

	while (m_GameIsRun)
	{
		double elapsedUpdateTime = m_GameTime->GetMilliseconds() - m_GameTime->TotalRealTime;

		if (m_IsFixedTimeStep)
		{
			while (elapsedUpdateTime < m_TargetElapsedTime)
			{
				Delay(m_TargetElapsedTime - elapsedUpdateTime);

				elapsedUpdateTime = m_GameTime->GetMilliseconds() - m_GameTime->TotalRealTime;
			}

			m_GameTime->ElapsedGameTime = m_TargetElapsedTime;
			m_GameTime->TotalGameTime += m_TargetElapsedTime;
		}
		else
		{
			m_GameTime->ElapsedGameTime = elapsedUpdateTime;
			m_GameTime->TotalGameTime += elapsedUpdateTime;
		}

		m_GameTime->ElapsedRealTime = elapsedUpdateTime;
		m_GameTime->TotalRealTime += elapsedUpdateTime;

		Update(m_GameTime);

		elapsedUpdateTime = m_GameTime->GetMilliseconds() - m_GameTime->TotalRealTime;

		if (m_IsFixedTimeStep && elapsedUpdateTime > m_TargetElapsedTime)
			m_GameTime->IsRunningSlowly = true;
		else
			m_GameTime->IsRunningSlowly = false;

		Draw(m_GameTime);
	}

	//double nextTime = m_GameTime->GetElapsedRealTime();

	//int skippedFrames = 1;

	//while (m_GameIsRun)
	//{
	//	// convert the time to seconds
	//	double currentTime = m_GameTime->GetElapsedRealTime();

	//	if ((currentTime - nextTime) > MAX_TIME_DIFFERENT) 
	//		nextTime = currentTime;

	//	if (currentTime >= nextTime)
	//	{
	//		// assign the time for the next update
	//		nextTime += TargetElapsedTime;

	//		Update(m_GameTime);
	//		//GameWindow->SetCaption("Update");

	//		if (currentTime < nextTime || skippedFrames > MAX_SKIPPED_FRAMES)
	//		{
	//			RedrawScene();
	//			//GameWindow->SetCaption("Draw");

	//			skippedFrames = 1;
	//		}
	//		else
	//		{
	//			skippedFrames++;
	//			//GameWindow->SetCaption("Skipping Frames");
	//		}
	//	}
	//	else
	//	{
	//		// calculate the time to sleep
	//		double sleepTime = (nextTime - currentTime);

	//		// sanity check
	//		if (sleepTime > 0.0f)
	//		{
	//			// sleep until the next update
	//			//
	//			static cTimer* timer = new cTimer();
	//			//
	//			while (timer->GetMilliseconds() < sleepTime)
	//			{
	//				// Do nothing
	//				//GameWindow->SetCaption("Sleep");
	//			}
	//		}
	//	}

	//	m_GameTime->ResetGameTime();
	//}
}

void cGame::Run(bool FullScreen, std::string Caption)
{
	m_GameWindow = new cGameWindow(Caption);
	m_SpriteBatch = new cSpriteBatch(Window->CreateWindow(FullScreen));
	//
	RunCore();
}

void cGame::Run(bool FullScreen, int Width, int Height, std::string Caption)
{
	m_GameWindow = new cGameWindow(Width, Height, Caption);
	m_SpriteBatch = new cSpriteBatch(Window->CreateWindow(FullScreen));
	//
	RunCore();
}

void cGame::Run(int Width, int Height, std::string Caption)
{
	m_GameWindow = new cGameWindow(Width, Height, Caption);
	m_SpriteBatch = new cSpriteBatch(Window->CreateWindow(false));
	//
	RunCore();
}

void cGame::LoadGame()
{

}

void cGame::Update(cGameTime* GameTime)
{

}

void cGame::Draw(cGameTime* GameTime)
{
	m_SpriteBatch->Flush();
}