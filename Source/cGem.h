#pragma once

#include "Engine\Vector.h"
#include "Engine\Circle.h"
#include "Engine\cGameTime.h"
#include "Engine\cSpriteBatch.h"
#include "Engine\cContentManager.h"
#include "Engine\cAudio.h"
#include "Tile.h"

class cGem
{
public:
	static const int PointValue;

public:
	cGem(cContentManager *Content, cAudio *Audio, Vector Position);
	~cGem(void);

private:
	void LoadContent(cContentManager *Content);

public:
	__declspec(property(get = GetPosition)) Vector Position;
	Vector GetPosition(void) { return (m_BasePosition + Vector(0.0f, m_Bounce)); }

	__declspec(property(get = GetBoundingCircle)) Circle BoundingCircle;
	Circle GetBoundingCircle(void) { return Circle(Position, Tile::Width / 3.0f); }

	void Update(cGameTime *GameTime);
	void Draw(cGameTime *GameTime, cSpriteBatch *SpriteBatch);
	void OnCollected(void);

private:
	cTexture *m_Texture;
	cAudio *m_Audio;
	Vector m_Origin;

    // The gem is animated from a base position along the Y axis.
	Vector m_BasePosition;
	float m_Bounce;
};
