#pragma once

#include <vector>
#include "Engine\Rectangle.h"
#include "Engine\cAudio.h"
#include "Engine\cContentManager.h"
#include "Engine\cAnimation.h"
#include "Engine\cAnimationPlayer.h"
#include "Tile.h"


class cEnemy
{
public:
	static const int PointValue;

private:
	static const float MaxWaitTime;
	static const float MoveSpeed;

public:
	cEnemy(cContentManager* Content, cAudio *Audio, Vector Position, std::string SpriteSet);
	~cEnemy(void);

private:
	void LoadContent(std::string SpriteSet);
	TileCollision cEnemy::GetCollision(int X, int Y);

public:
	__declspec(property(get = GetBoundingRectangle)) Rectangle BoundingRectangle;
	Rectangle GetBoundingRectangle(void)
	{
		//int left = (int)Round(m_Position.X - m_Sprite->Origin.X) + m_LocalBounds.X;
        //int top = (int)Round(m_Position.Y - m_Sprite->Origin.Y) + m_LocalBounds.Y;

		int left = m_Position.X - m_Sprite->Origin.X + m_LocalBounds.X;
        int top = m_Position.Y - m_Sprite->Origin.Y + m_LocalBounds.Y;

        return Rectangle(left, top, m_LocalBounds.Width, m_LocalBounds.Height);
	}
	
	__declspec(property(get = GetPosition)) Vector Position;
	Vector GetPosition(void) { return m_Position; }
	
	__declspec(property(get = GetIsAlive)) bool IsAlive;
	bool GetIsAlive(void) { return m_IsAlive; }
	
	__declspec(property(get = GetCanErase)) bool CanErase;
	bool GetCanErase(void) { return (m_Sprite->FrameIndex + 1 >= m_DieAnimation->FrameCount); }

	void SetTiles(std::vector<std::vector<Tile>> TilesArray);
	void OnIdleAnimation(void);
	void OnKilled();

	void Update(cGameTime *GameTime);
	void Draw(cGameTime *GameTime, cSpriteBatch *SpriteBatch);

private:
	Vector m_Position;
	std::vector<std::vector<Tile>> m_TilesArray;
	cAudio *m_Audio;
	cContentManager* m_Content;
	Rectangle m_LocalBounds;
	cAnimation *m_IdleAnimation, *m_RunAnimation, *m_DieAnimation;
	cAnimationPlayer *m_Sprite;
	int m_FaceDirection;
	float m_WaitTime;
	float m_Time;
	bool m_IsAlive;
};
