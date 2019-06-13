
#include "Rectangle.h"
#include "Mathematics.h"

#pragma once

struct Circle
{
public:
	Circle(Vector Center, float Radius) :
		  m_Center(Center),
		  m_Radius(Radius)
	{
	}

public:
	__declspec(property(get = GetCenter)) Vector Center;
	Vector GetCenter(){ return m_Center; }

	__declspec(property(get = GetRadius)) int Radius;
	int GetRadius(){ return (int)m_Radius; }

	bool Intersects(Rectangle Rectangle)
    {
		Vector v = Vector(Clamp((float)m_Center.X, (float)Rectangle.Left, (float)Rectangle.Right), 
			Clamp((float)m_Center.Y, (float)Rectangle.Top, (float)Rectangle.Bottom));

        Vector direction = m_Center - v;

		float magnitude = direction.Magnitude;

		return ((magnitude > 0) && (magnitude < Squared(m_Radius)));
    }

private:
	Vector m_Center;
	float m_Radius;
};