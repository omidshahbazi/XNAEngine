#include "cPlayer.h"

//const float cPlayer::MoveAcceleration = 9000.0f;
//const float cPlayer::MaxMoveSpeed = 3000.0f;
//const float cPlayer::GroundDragFactor = 0.88f;
//const float cPlayer::AirDragFactor = 0.77f;
//
//const float cPlayer::MaxJumpTime = 0.2f;
//const float cPlayer::JumpLaunchVelocity = -1800.0f;
//const float cPlayer::GravityAcceleration = 4000.0f;
//const float cPlayer::MaxFallSpeed = 1000.0f;
//const float cPlayer::JumpControlPower = 0.15f;

const float cPlayer::MoveAcceleration = 5000.0f;
const float cPlayer::MaxMoveSpeed = 3000.0f;
const float cPlayer::GroundDragFactor = 0.88f;
const float cPlayer::AirDragFactor = 0.85f;

const float cPlayer::MaxJumpTime = 0.2f;
const float cPlayer::JumpLaunchVelocity = -1800.0f;
const float cPlayer::GravityAcceleration = 4000.0f;
const float cPlayer::MaxFallSpeed = 1000.0f;
const float cPlayer::JumpControlPower = 0.15f;

//const float cPlayer::MoveAcceleration = 1400.0f;
//const float cPlayer::MaxMoveSpeed = 2000.0f;
//const float cPlayer::GroundDragFactor = 0.58f;
//const float cPlayer::AirDragFactor = 0.65f;
//
//const float cPlayer::MaxJumpTime = 0.35f;
//const float cPlayer::JumpLaunchVelocity = -4000.0f;
//const float cPlayer::GravityAcceleration = 3500.0f;
//const float cPlayer::MaxFallSpeed = 600.0f;
//const float cPlayer::JumpControlPower = 0.14f;

cPlayer::cPlayer(std::vector<std::vector<Tile>> TilesArray, cInput* Input, cContentManager* Content, cAudio *Audio, Vector Position)
{
	m_TilesArray = TilesArray;
	m_Input = Input;
	m_Content = Content;
	m_Audio = Audio;
	m_FaceDirection = 1;

	LoadContent();

	Reset(Position);
}

cPlayer::~cPlayer(void)
{
	delete m_IdleAnimation;
	delete m_RunAnimation;
	delete m_JumpAnimation;
	delete m_CelebrateAnimation;
	delete m_DieAnimation;
}

void cPlayer::LoadContent(void)
{
	m_IsKilling = false;

	std::string SpriteSet = "Sprites\\Player\\";

	m_IdleAnimation = new cAnimation(m_Content->LoadTexture(SpriteSet + "Idle.bmp", Color(0, 0, 0)), 1.0f, true);
	m_RunAnimation = new cAnimation(m_Content->LoadTexture(SpriteSet + "Run.bmp", Color(0, 0, 0)), 0.05f, true);
	m_JumpAnimation = new cAnimation(m_Content->LoadTexture(SpriteSet + "Jump.bmp", Color(0, 0, 0)), 0.05f, false);
	m_CelebrateAnimation = new cAnimation(m_Content->LoadTexture(SpriteSet + "Celebrate.bmp", Color(0, 0, 0)), 0.02f, false);
	m_DieAnimation = new cAnimation(m_Content->LoadTexture(SpriteSet + "Die.bmp", Color(0, 0, 0)), 0.03f, false);
	m_KillAnimation = new cAnimation(m_Content->LoadTexture(SpriteSet + "Kill.bmp", Color(0, 0, 0)), 0.009f, false);

	int width = (int)(m_IdleAnimation->FrameWidth * 0.4);
    int left = (m_IdleAnimation->FrameWidth - width) / 2;
    int height = (int)(m_IdleAnimation->FrameWidth * 0.8);
    int top = m_IdleAnimation->FrameHeight - height;

	m_LocalBounds = Rectangle(left, top, width, height);
}

void cPlayer::Reset(Vector Position)
{
	m_Position = Position;
	m_Velocity = Vector();
	m_IsAlive = true;

	m_Sprite = new cAnimationPlayer();
	m_Sprite->PlayAnimation(m_IdleAnimation);
}

void cPlayer::Update(cGameTime *GameTime)
{
	m_IsKilling = false;

	GetInput();

	ApplyPhysics(GameTime);
	
	if (m_IsAlive && m_IsOnGround)
	{
		if (m_IsKilling)
		{
			m_Sprite->PlayAnimation(m_KillAnimation);
		}
		else if (Abs(m_Velocity.X) - 0.02f > 0)
		{
			m_Sprite->PlayAnimation(m_RunAnimation);
		}
		else
			m_Sprite->PlayAnimation(m_IdleAnimation);
	}

	m_Movement = 0.0f;
	m_IsJumping = false;
}

void cPlayer::GetInput()
{
	if (m_Input->IsKeyHeld(SDLK_LEFT) ||
		m_Input->IsKeyHeld(SDLK_a))
    {
		m_Movement = 1.0f;
        m_FaceDirection = -1.0f;
    }
	else if (m_Input->IsKeyHeld(SDLK_RIGHT) ||
             m_Input->IsKeyHeld(SDLK_d))
    {
        m_Movement = m_FaceDirection = 1.0f;
    }

	switch (m_Input->GetDownedKey())
		{
			case SDLK_SPACE:
			case SDLK_w:
			case SDLK_UP:
				{
  					m_IsJumping = true;
				} break;

			case SDLK_LSHIFT:
			case SDLK_RSHIFT:
				{
  					m_IsKilling = true;
				} break;
		}
}

void cPlayer::ApplyPhysics(cGameTime *GameTime)
{
	float elapsed = (float)GameTime->ElapsedGameTime / 1000.0f;

	Vector previousPosition = m_Position;

	// Base velocity is a combination of horizontal movement control and
	// acceleration downward due to gravity.
	m_Velocity.X += (m_FaceDirection * m_Movement * MoveAcceleration * elapsed);
	m_Velocity.Y = Clamp(m_Velocity.Y + GravityAcceleration * elapsed, -MaxFallSpeed, MaxFallSpeed);
   
	m_Velocity.Y = DoJump(m_Velocity.Y, GameTime);

	// Apply pseudo-drag horizontally.
	if (m_IsOnGround)
		m_Velocity.X *= GroundDragFactor;
	else
		m_Velocity.X *= AirDragFactor;

	// Prevent the player from running faster than his top speed.            
	m_Velocity.X = Clamp((float)m_Velocity.X, -MaxMoveSpeed, MaxMoveSpeed);

	// Apply velocity.
	m_Position += m_Velocity * elapsed;
	m_Position = Vector((float)Round(m_Position.X), (float)Round(m_Position.Y));

	// If the player is now colliding with the level, separate them.
	HandleCollisions();

	// If the collision stopped us from moving, reset the velocity to zero.
	if (m_Position.X == previousPosition.X)
		m_Velocity.X = 0;

	if (m_Position.Y == previousPosition.Y)
		m_Velocity.Y = 0;

	if (m_IsKilling)
		m_Position = previousPosition;
}

void cPlayer::HandleCollisions(void)
{
    // Get the player's bounding rectangle and find neighboring tiles.
    Rectangle bounds = BoundingRectangle;
    int leftTile = (int)Floor((float)bounds.Left / Tile::Width) - 1;
    int rightTile = (int)Ceiling(((float)bounds.Right / Tile::Width)) - 1;
    int topTile = (int)Floor((float)bounds.Top / Tile::Height);
    int bottomTile = (int)Ceiling(((float)bounds.Bottom / Tile::Height)) - 1;

    // Reset flag to search for ground collision.
    m_IsOnGround = false;

    // For each potentially colliding tile,
    for (int y = topTile; y <= bottomTile; ++y)
    {
        for (int x = leftTile; x <= rightTile; ++x)
        {
            // If this tile is collidable,
            TileCollision collision = GetCollision(x, y);

            if (collision != TileCollision_Passable)
            {
                // Determine collision depth (with direction) and magnitude.
                Rectangle tileBounds = GetBounds(x, y);

                Vector depth = bounds.GetIntersectionDepth(tileBounds);

                if (depth != Vector())
                {
                    float absDepthX = Abs((float)depth.X);
                    float absDepthY = Abs((float)depth.Y);

                    // Resolve the collision along the shallow axis.
                    if (absDepthY < absDepthX || collision == TileCollision_Platform)
                    {
                        // If we crossed the top of a tile, we are on the ground.
 						if (m_PreviousBottom <= tileBounds.Top)
                            m_IsOnGround = true;

                        // Ignore platforms, unless we are on the ground.
                        if (collision == TileCollision_Impassable || m_IsOnGround)
                        {
                            // Resolve the collision along the Y axis.
                            m_Position = Vector((float)m_Position.X, (float)(m_Position.Y + depth.Y));

                            // Perform further collisions with the new bounds.
                            bounds = BoundingRectangle;
                        }
                    }
                    else if (collision == TileCollision_Impassable) // Ignore platforms.
                    {
                        // Resolve the collision along the X axis.
                        m_Position = Vector((float)(m_Position.X + depth.X), (float)m_Position.Y);

                        // Perform further collisions with the new bounds.
                        bounds = BoundingRectangle;
                    }
                }
            }
        }
    }

    // Save the new bounds bottom.
 	m_PreviousBottom = bounds.Bottom;
}

float cPlayer::DoJump(float VelocityY, cGameTime *GameTime)
{
	// If the player wants to jump
	if (m_IsJumping)
    {
        // Begin or continue a jump
        if ((!m_WasJumping && m_IsOnGround) || m_JumpTime > 0.0f)
        {
            if (m_JumpTime == 0.0f)
				m_Audio->Play("Data\\Sounds\\PlayerJump.ogg");

            m_JumpTime += (float)GameTime->ElapsedGameTime / 1000.0f;
			m_Sprite->PlayAnimation(m_JumpAnimation);
        }

        // If we are in the ascent of the jump
        if (0.0f < m_JumpTime && m_JumpTime <= MaxJumpTime)
        {
            // Fully override the vertical velocity with a power curve that gives players more control over the top of the jump
            VelocityY = JumpLaunchVelocity * (1.0f - (float)Power(m_JumpTime / MaxJumpTime, JumpControlPower));
        }
        else
        {
            // Reached the apex of the jump
            m_JumpTime = 0.0f;
        }
    }
    else
    {
        // Continues not jumping or cancels a jump in progress
        m_JumpTime = 0.0f;
    }

	m_WasJumping = m_IsJumping;

    return VelocityY;
}

TileCollision cPlayer::GetCollision(int X, int Y)
{
    // Prevent escaping past the level ends.
    if (X < 0 || X >= Width)
        return TileCollision_Impassable;
    // Allow jumping past the level top and falling through the bottom.
    if (Y < 0 || Y >= Height)
        return TileCollision_Passable;

    return m_TilesArray[Y][X].Collision;
}

Rectangle cPlayer::GetBounds(int X, int Y)
{
	return Rectangle(X * Tile::Width, Y * Tile::Height, Tile::Width, Tile::Height);
}

void cPlayer::Draw(cGameTime *GameTime, cSpriteBatch *SpriteBatch)
{
	SpriteEffects effect = SpriteEffects();
	effect.Flip = m_FaceDirection > 0 ? SpriteFlip_FlipHorizontally : SpriteFlip_None;

    // Draw that sprite.

	m_Sprite->Draw(GameTime, SpriteBatch, m_Position, effect);
}

void cPlayer::OnKilled(cEnemy *KilledBy)
{
	m_IsAlive = false;

    if (KilledBy != NULL)
		m_Audio->Play("Data\\Sounds\\PlayerKilled.ogg");
    else
		m_Audio->Play("Data\\Sounds\\PlayerFall.ogg");

    m_Sprite->PlayAnimation(m_DieAnimation);
}

void cPlayer::OnReachedExit(void)
{
	m_Audio->Play("Data\\Sounds\\ExitReached.ogg");

	m_Sprite->PlayAnimation(m_CelebrateAnimation);
}