#pragma once

#include <vector>
#include "cEnemy.h"
#include "Tile.h"
#include "Engine\cAnimationPlayer.h"
#include "Engine\Mathematics.h"
#include "Engine\cInput.h"
#include "Engine\cContentManager.h"
#include "Engine\cAudio.h"

class cPlayer
{
private:
	static const float MoveAcceleration;
	static const float MaxMoveSpeed;
	static const float GroundDragFactor;
	static const float AirDragFactor;

	// Constants for controlling vertical movement
	static const float MaxJumpTime;
	static const float JumpLaunchVelocity;
	static const float GravityAcceleration;
	static const float MaxFallSpeed;
	static const float JumpControlPower;

public:
	cPlayer(std::vector<std::vector<Tile>> TilesArray, cInput* Input, cContentManager* Content, cAudio *Audio, Vector Position);
	~cPlayer(void);

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

	__declspec(property(get = GetIsAlive)) bool IsAlive;
	bool GetIsAlive(void) { return m_IsAlive; }

	__declspec(property(get = GetIsOnGround)) bool IsOnGround;
	bool GetIsOnGround(void) { return m_IsOnGround; }

	__declspec(property(get = GetIsKilling)) bool IsKilling;
	bool GetIsKilling(void) { return m_IsKilling; }

	void Reset(Vector Position);
	void Update(cGameTime *GameTime);
	void Draw(cGameTime *GameTime, cSpriteBatch *SpriteBatch);
	void ApplyPhysics(cGameTime *GameTime);
	void OnKilled(cEnemy *KilledBy);
	void OnReachedExit(void);

private:
	__declspec(property(get = GetWidth)) int Width;
	int GetWidth(void) { return m_TilesArray[0].size(); }

	__declspec(property(get = GetHeight)) int Height;
	int GetHeight(void) { return m_TilesArray.size(); }

	void LoadContent(void);
	void GetInput(void);
	float DoJump(float VelocityY, cGameTime *GameTime);
	void HandleCollisions(void);
	TileCollision GetCollision(int X, int Y);
	Rectangle GetBounds(int X, int Y);

private:
	std::vector<std::vector<Tile>> m_TilesArray;
	cInput* m_Input;
	cContentManager* m_Content;
	cAnimation *m_IdleAnimation, *m_RunAnimation, *m_JumpAnimation, *m_CelebrateAnimation, *m_DieAnimation, *m_KillAnimation;
	cAudio *m_Audio;
	cAnimationPlayer *m_Sprite;
	bool m_IsAlive, m_IsOnGround, m_IsJumping, m_WasJumping, m_IsKilling;
	Vector m_Position, m_Velocity;
	float m_PreviousBottom, m_Movement, m_JumpTime;
	Rectangle m_LocalBounds;
	int m_FaceDirection;
};
