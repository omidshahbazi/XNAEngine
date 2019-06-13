#include "cEnemy.h"

const int cEnemy::PointValue = 60;
const float cEnemy::MaxWaitTime = 1.0f;
const float cEnemy::MoveSpeed = 260.0f;

cEnemy::cEnemy(cContentManager* Content, cAudio *Audio, Vector Position, std::string SpriteSet)
{
	m_Content = Content;
	m_Audio = Audio;
	m_Position = Position;

	m_Sprite = new cAnimationPlayer();

	LoadContent(SpriteSet);
}

cEnemy::~cEnemy(void)
{
}

void cEnemy::LoadContent(std::string SpriteSet)
{
	m_FaceDirection = 1;
	m_IsAlive = true;

    SpriteSet = "Sprites/" + SpriteSet + "/";

    m_RunAnimation = new cAnimation(m_Content->LoadTexture(SpriteSet + "Run.bmp", Color(0, 0, 0)), 0.1f, true);
    m_IdleAnimation = new cAnimation(m_Content->LoadTexture(SpriteSet + "Idle.bmp", Color(0, 0, 0)), 0.1f, true);
	m_DieAnimation = new cAnimation(m_Content->LoadTexture(SpriteSet + "Die.bmp", Color(0, 0, 0)), 0.03f, false);

    m_Sprite->PlayAnimation(m_IdleAnimation);

    // Calculate bounds within texture size.
    int width = (int)(m_IdleAnimation->FrameWidth * 0.35);
    int left = (m_IdleAnimation->FrameWidth - width) / 2;
    int height = (int)(m_IdleAnimation->FrameWidth * 0.7);
    int top = m_IdleAnimation->FrameHeight - height;
    m_LocalBounds = Rectangle(left, top, width, height);
}

void cEnemy::SetTiles(std::vector<std::vector<Tile>> TilesArray)
{
	m_TilesArray = TilesArray;
}

void cEnemy::OnIdleAnimation(void)
{
	m_WaitTime = MaxWaitTime;

	m_Sprite->PlayAnimation(m_IdleAnimation);
}

void cEnemy::OnKilled()
{
	if (m_IsAlive)
	{
		m_IsAlive = false;

		m_Audio->Play("Data\\Sounds\\EnemyKilled.ogg");

		m_Sprite->PlayAnimation(m_DieAnimation);
	}
}

void cEnemy::Update(cGameTime *GameTime)
{
	if (m_IsAlive)
	{
		float elapsed = (float)GameTime->ElapsedGameTime / 1000.0f;

		// Calculate tile position based on the side we are walking towards.
		float posX = Position.X + m_LocalBounds.Width / 2 * m_FaceDirection;

		int tileX = (int)Floor(posX / Tile::Width) - m_FaceDirection;
		int tileY = (int)Floor(Position.Y / Tile::Height);

		if (m_WaitTime > 0)
		{
			// Wait for some amount of time.
			m_WaitTime = Max(0.0f, m_WaitTime - elapsed);

			if (m_WaitTime <= 0.0f)
			{
				// Then turn around.
				m_FaceDirection = -m_FaceDirection;
			}
		}
		else
		{
			// If we are about to run into a wall or off a cliff, start waiting.
			if (GetCollision(tileX + m_FaceDirection, tileY - 1) == TileCollision_Impassable ||
				GetCollision(tileX + m_FaceDirection, tileY) == TileCollision_Passable)
			{
				m_WaitTime = MaxWaitTime;
			}
			else
			{
				// Move in the current direction.
				Vector velocity = Vector(m_FaceDirection * MoveSpeed * elapsed, 0.0f);
				m_Position = m_Position + velocity;
			}
		}
	
		if (m_WaitTime > 0)
			m_Sprite->PlayAnimation(m_IdleAnimation);
		else
			m_Sprite->PlayAnimation(m_RunAnimation);
	}
}

TileCollision cEnemy::GetCollision(int X, int Y)
{
    // Prevent escaping past the level ends.
	if (X < 0 || X >= m_TilesArray[0].size())
        return TileCollision_Impassable;
    // Allow jumping past the level top and falling through the bottom.
	if (Y < 0 || Y >= m_TilesArray.size())
        return TileCollision_Passable;

    return m_TilesArray[Y][X].Collision;
}

void cEnemy::Draw(cGameTime *GameTime, cSpriteBatch *SpriteBatch)
{
    // Draw facing the way the enemy is moving.
	SpriteEffects effect = SpriteEffects();
	effect.Flip = m_FaceDirection > 0 ? SpriteFlip_FlipHorizontally : SpriteFlip_None;

    m_Sprite->Draw(GameTime, SpriteBatch, Position, effect);

	//printf(IntToString((int)elapsed).c_str());
}