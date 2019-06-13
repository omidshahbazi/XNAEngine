
#include "cState.h"

cState::cState(cContentManager *Content, cInput *Input)
{
	m_Content = Content;
	m_Input = Input;
}

cState::~cState(void)
{
}

void cState::Update(cGameTime *GameTime)
{
}

void cState::Draw(cGameTime *GameTime, cSpriteBatch *SpriteBatch)
{
}