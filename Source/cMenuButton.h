#pragma once

#include <string>
#include "Engine\cTexture.h"
#include "Engine\cSpriteBatch.h"
#include "Engine\cFont.h"

class cMenuButton
{
public:
	cMenuButton(cTexture *Texture, Vector Position, cFont *Font, std::string Text, Vector TextOffset);
	~cMenuButton(void);

public:
	__declspec(property(get = GetBoundingRectangle)) Rectangle BoundingRectangle;
	Rectangle GetBoundingRectangle(void) 
	{
		return Rectangle(m_Position, 
			Vector(
			(float)(m_Texture->Width * m_Effects->ZoomX), 
			(float)(m_Texture->Height * m_Effects->ZoomX)
			/*, 
			m_Texture->Height * m_Effects->ZoomY*/)); 
	}

	__declspec(property(get = GetTexture, put = SetTexture)) cTexture *Texture;
	cTexture* GetTexture(void) { return m_Texture; }
	void SetTexture(cTexture *Value) { m_Texture = Value; }

	__declspec(property(get = GetEffects)) SpriteEffects *Effect;
	SpriteEffects* GetEffects(void) { return m_Effects; }

	void Draw(cSpriteBatch *SpriteBatch);

private:
	cTexture *m_Texture;
	Vector m_Position;
	cFont *m_Font;
	std::string m_Text;
	Vector m_TextOffset;
	SpriteEffects *m_Effects;
};
