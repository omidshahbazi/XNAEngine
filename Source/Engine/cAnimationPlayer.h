#pragma once

#include "Engine\General.h"
#include "Engine\cGameTime.h"
#include "Engine\cSpriteBatch.h"
#include "Engine\Mathematics.h"
#include "Engine\cAnimation.h"

class cAnimationPlayer
{
public:
	cAnimationPlayer()
	{
		m_Animation = 0;
        m_FrameIndex = 0;
        m_Time = 0.0f;
	}

public:
	void PlayAnimation(cAnimation* Animation)
	{
		if (m_Animation == Animation)
                return;

        m_Animation = Animation;
        m_FrameIndex = 0;
        m_Time = 0.0f;
	}

    void Draw(cGameTime* GameTime, cSpriteBatch* SpriteBatch, Vector Position, SpriteEffects Effects)
    {
        m_Time += (float)GameTime->ElapsedGameTime / 1000;

		while (m_Time > m_Animation->FrameTime)
        {
            m_Time -= m_Animation->FrameTime;

			if (m_Animation->IsLooping)
            {
                m_FrameIndex = (m_FrameIndex + 1) % m_Animation->FrameCount;
            }
            else
            {
				m_FrameIndex = (int)Min((float)(m_FrameIndex + 1), (float)(m_Animation->FrameCount - 1));
            }
        }

		Rectangle source = Rectangle(m_FrameIndex * m_Animation->Texture->Height, 0, m_Animation->Texture->Height, m_Animation->Texture->Height);
		
		Effects.Origin = Origin;

        SpriteBatch->Draw(m_Animation->Texture, source, Position, Effects);
    }

public:
	__declspec(property(get = GetAnimation)) cAnimation* Animation;
	cAnimation* GetAnimation(void) { return m_Animation; }
	
	__declspec(property(get = GetFrameIndex)) int FrameIndex;
	int GetFrameIndex(void) { return m_FrameIndex; }
	
	__declspec(property(get = GetOrigin)) Vector Origin;
	Vector GetOrigin(void) { return Vector(m_Animation->FrameWidth / 2.0f, (float)m_Animation->FrameHeight); }

private:
	cAnimation* m_Animation;
	int m_FrameIndex;
	float m_Time;
};