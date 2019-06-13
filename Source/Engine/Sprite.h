#pragma once

#include "cTexture.h"
#include "Rectangle.h"
#include "Vector.h"

enum SpriteType
{
	SpriteType_Text = 0,
	SpriteType_Texture = 1
};

enum SpriteFlip
{
	SpriteFlip_None = 0,
    SpriteFlip_FlipHorizontally = 1,
    SpriteFlip_FlipVertically = 256,
};

struct SpriteEffects
{
public:
	SpriteEffects() :
			m_Flip(SpriteFlip_None),
			m_Rotation(0.0f),
			m_RotationAround(Vector()),
			m_ZoomX(1.0f),
			m_ZoomY(1.0f),
			m_Smooth(10),
			m_Origin(Vector())
		{
		}

public:
	__declspec(property(get = GetFlip, put = SetFlip)) SpriteFlip Flip;
	SpriteFlip GetFlip(void) { return m_Flip; }
	void SetFlip(SpriteFlip Value) { m_Flip = Value; }

	__declspec(property(get = GetRotation, put = SetRotation)) double Rotation;
	double GetRotation(void) { return m_Rotation; }
	void SetRotation(double Value) { m_Rotation = Value; }
	
	__declspec(property(get = GetRotationAround, put = SetRotationAround)) Vector RotationAround;
	Vector GetRotationAround(void) { return m_RotationAround; }
	void SetRotationAround(Vector Value) { m_RotationAround = Value; }
	
	__declspec(property(get = GetZoomX, put = SetZoomX)) double ZoomX;
	double GetZoomX(void) { return m_ZoomX; }
	void SetZoomX(double Value) { m_ZoomX = Value; }
	
	__declspec(property(get = GetZoomY, put = SetZoomY)) double ZoomY;
	double GetZoomY(void) { return m_ZoomY; }
	void SetZoomY(double Value) { m_ZoomY = Value; }
	
	__declspec(property(get = GetSmooth, put = SetSmooth)) int Smooth;
	int GetSmooth(void) { return m_Smooth; }
	void SetSmooth(int Value) { m_Smooth = Value; }
	
	__declspec(property(get = GetOrigin, put = SetOrigin)) Vector Origin;
	Vector GetOrigin(void) { return m_Origin; }
	void SetOrigin(Vector Value) { m_Origin = Value; }

private:
	SpriteFlip m_Flip;
	double m_Rotation;
	Vector m_RotationAround;
	double m_ZoomX;
	double m_ZoomY;
	int m_Smooth;
	Vector m_Origin;
};

struct Sprite
{
public:
	// Text Sprites
	Sprite(cTexture *Texture, 
		Rectangle DestinationRectangle, 
		SpriteEffects Effect) :

		m_Texture(Texture), 
		m_DestinationRectangle(DestinationRectangle), 
		m_Effect(Effect),
		m_Type(SpriteType_Text)
		{}
	// Texture Sprites
	Sprite(cTexture *Texture, 
		Rectangle SourceRectangle, 
		Rectangle DestinationRectangle,
		SpriteEffects Effect) :

		m_Texture(Texture), 
		m_SourceRectangle(SourceRectangle), 
		m_DestinationRectangle(DestinationRectangle), 
		m_Effect(Effect),
		m_Type(SpriteType_Texture)
		{}

public:
	__declspec(property(get = GetSurfaceType)) SpriteType SurfaceType;
	SpriteType GetSurfaceType(void) { return m_Type; }

	__declspec(property(get = GetTexture)) cTexture* Texture;
	cTexture* GetTexture(void) { return m_Texture; }
	
	__declspec(property(get = GetSourceRectangle)) Rectangle SourceRectangle;
	Rectangle GetSourceRectangle(void) { return m_SourceRectangle; }
	
	__declspec(property(get = GetDestinationRectangle)) Rectangle DestinationRectangle;
	Rectangle GetDestinationRectangle(void) { return m_DestinationRectangle; }
	
	__declspec(property(get = GetEffect)) SpriteEffects Effect;
	SpriteEffects GetEffect(void) { return m_Effect; }

private:
	SpriteType m_Type;
	cTexture *m_Texture;
	Rectangle m_SourceRectangle;
	Rectangle m_DestinationRectangle;
	SpriteEffects m_Effect;
};