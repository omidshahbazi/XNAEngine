#include "cGem.h"

const int cGem::PointValue = 30;

cGem::cGem(cContentManager *Content, cAudio *Audio, Vector Position)
{
	m_Bounce = 0;

	m_BasePosition = Position;

	LoadContent(Content);

	m_Audio = Audio;
}

cGem::~cGem(void)
{
	delete m_Texture;
}

void cGem::LoadContent(cContentManager *Content)
{
	m_Texture = Content->LoadTexture("Sprites/Gem.bmp", Color(0, 0, 0));

	m_Origin = Vector(m_Texture->Width / 2.0f, m_Texture->Height / 2.0f);
}

void cGem::Update(cGameTime *GameTime)
{
    // Bounce control constants
    const float BounceHeight = 0.18f;
    const float BounceRate = 10.0f;
    const float BounceSync = -0.75f;

    // Bounce along a sine curve over time.
    // Include the X coordinate so that neighboring gems bounce in a nice wave pattern.
	double t = GameTime->TotalGameTime / 1000.0f * BounceRate + Position.X * BounceSync;
    m_Bounce = (float)Sin(t) * BounceHeight * m_Texture->Height;
}

void cGem::Draw(cGameTime *GameTime, cSpriteBatch *SpriteBatch)
{
	SpriteEffects effect = SpriteEffects();
	effect.Origin = m_Origin;

	Vector pos = (m_BasePosition + Vector(0.0f, m_Bounce));

	SpriteBatch->Draw(m_Texture, Vector(), pos, effect);
}

void cGem::OnCollected(void)
{
	m_Audio->Play("Data\\Sounds\\GemCollected.ogg");
}