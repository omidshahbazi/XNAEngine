
#include "General.h"
#include "cGameTime.h"
#include "cGameWindow.h"
#include "cInput.h"
#include "cSpriteBatch.h"
#include "cContentManager.h"
#include "cAudio.h"

#pragma once

#define DEFAULT_FRAME_RATE 60
#define MAX_TIME_DIFFERENT 0.5f
#define MAX_SKIPPED_FRAMES 5

class cGame
{
public:
	cGame(bool InitializeVideo, bool InitializeAudio, bool InitilizeContentManager)
	{
		Initialize(InitializeVideo, InitializeAudio, InitilizeContentManager);

		m_GameTime = new cGameTime();

		m_Input = new cInput();

		m_IsFixedTimeStep = true;

		m_TargetElapsedTime = 1000.0f / DEFAULT_FRAME_RATE;
	}

	~cGame(void)
	{
		delete Input;
		delete m_GameTime;
		delete SpriteBatch;

		SDL_Quit();
	}

public:
	void Run(bool FullScreen, std::string Caption);
	void Run(bool FullScreen, int Width, int Height, std::string Caption);
	void Run(int Width, int Height, std::string Caption);
	void Exit(void)
	{
		m_GameIsRun = false;
	}
	void RedrawScene(void)
	{
		SpriteBatch->Clear();
		
		Draw(m_GameTime);
	}

public:
	virtual void LoadGame();
	virtual void Update(cGameTime* GameTime);
	virtual void Draw(cGameTime* GameTime);

private:
	void RunCore();
	void Initialize(bool InitializeVideo, bool InitializeAudio, bool InitilizeContentManager);

public:
	__declspec(property(get = GetWindow)) cGameWindow* Window;
	cGameWindow* GetWindow(void) { return m_GameWindow; }

	__declspec(property(get = GetMousePosition)) Vector MousePosition;
	Vector GetMousePosition(void) 
	{
		int x, y;

		SDL_PumpEvents();

		SDL_GetMouseState(&x, &y);
		
		return Vector((float)x, (float)y);
	}
	
	__declspec(property(get = GetInput)) cInput* Input;
	cInput* GetInput(void) { return m_Input; }
	
	__declspec(property(get = GetSpriteBatch)) cSpriteBatch* SpriteBatch;
	cSpriteBatch* GetSpriteBatch(void) { return m_SpriteBatch; }
	
	__declspec(property(get = GetContent, put = SetContent)) cContentManager* Content;
	cContentManager* GetContent(void) { return m_Content; }
	
	__declspec(property(get = GetAudioEngine)) cAudio* AudioEngine;
	cAudio* GetAudioEngine(void) { return m_AudioEngine; }

	__declspec(property(get = GetIsFixedTimeStep, put = SetIsFixedTimeStep)) bool IsFixedTimeStep;
	bool GetIsFixedTimeStep(void) { return m_IsFixedTimeStep; }
	void SetIsFixedTimeStep(bool value) { m_IsFixedTimeStep = value; }

	__declspec(property(get = GetTargetElapsedTime, put = SetTargetElapsedTime)) double TargetElapsedTime;
	double GetTargetElapsedTime(void) { return m_TargetElapsedTime; }
	void SetTargetElapsedTime(double x) { m_TargetElapsedTime = x; }

private:
	cGameWindow* m_GameWindow;
	cInput* m_Input;
	cSpriteBatch* m_SpriteBatch;
	cContentManager* m_Content;
	cAudio* m_AudioEngine;

	bool m_IsFixedTimeStep;
	bool m_GameIsRun;
	double m_TargetElapsedTime;
	cGameTime* m_GameTime;
};