#pragma once

#include "Engine\cInput.h"
#include "Engine\cGameTime.h"
#include "Engine\cSpriteBatch.h"
#include "Engine\cContentManager.h"

typedef enum States
{
	States_Intro = 0,
	States_Menu = 1,
	States_Game = 3
} States;

class cState
{
public:
	cState(cContentManager *Content, cInput *Input);
	~cState(void);

public:
	__declspec(property(get = GetContent)) cContentManager *Content;
	cContentManager* GetContent(void) { return m_Content; }

	__declspec(property(get = GetInput)) cInput *Input;
	cInput* GetInput(void) { return m_Input; }

	virtual void Update(cGameTime *GameTime);
	virtual void Draw(cGameTime *GameTime, cSpriteBatch *SpriteBatch);

private:
	cContentManager *m_Content;
	cInput *m_Input;
};
