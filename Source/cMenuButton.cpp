
#include "cMenuButton.h"

cMenuButton::cMenuButton(cTexture *Texture, Vector Position, cFont *Font, std::string Text, Vector TextOffset) :
	m_Texture(Texture),
	m_Position(Position),
	m_Font(Font),
	m_Text(Text),
	m_TextOffset(TextOffset)
{
	m_Effects = new SpriteEffects();
}

cMenuButton::~cMenuButton(void)
{
}

void cMenuButton::Draw(cSpriteBatch *SpriteBatch)
{
	SpriteBatch->Draw(m_Texture, m_Position, *m_Effects);

	double zoomX = m_Effects->ZoomX;
	m_Effects->ZoomX = 1.0f;

	SpriteBatch->DrawString(m_Font, m_Text, m_Position + m_TextOffset, Color(0, 0, 0), *m_Effects);

	m_Effects->ZoomX = zoomX;
}