#pragma once

#include "Mathematics.h"

struct Vector
{
public:
	Vector() :
		m_X(0),
		m_Y(0)
		{}

	Vector(float Value) :
		m_X(Value),
		m_Y(Value)
		{}

	Vector(float X, float Y) :
		m_X(X),
		m_Y(Y)
	{}

public:
	bool operator !=(Vector &other)
	{
		if (m_X == other.X && m_Y == other.Y)
			return false;

		return true;
	}

	Vector operator +(Vector &other) 
	{
		return Vector(m_X + other.X, m_Y + other.Y);
	}
	
	Vector operator +=(Vector &other) 
	{
		m_X += other.X;
		m_Y += other.Y;

		return Vector(m_X, m_Y);
	}
	
	Vector operator +=(float other) 
	{
		m_X += other;
		m_Y += other;

		return Vector(m_X, m_Y);
	}

	Vector operator -(Vector &other) 
	{
		return Vector(m_X - other.X, m_Y - other.Y);
	}

	Vector operator -=(Vector &other) 
	{
		m_X -= other.X;
		m_Y -= other.Y;

		return Vector(m_X, m_Y);
	}

	Vector operator -=(float other)
	{
		m_X -= other;
		m_Y -= other;

		return Vector(m_X, m_Y);
	}

	Vector operator *(Vector other) 
	{
		return Vector(m_X * other.X, m_Y * other.Y);
	}

	Vector operator *(Vector &other) 
	{
		return Vector(m_X * other.X, m_Y * other.Y);
	}

	Vector operator *(float &other) 
	{
		return Vector(m_X * other, m_Y * other);
	}

	Vector operator /(Vector other) 
	{
		return Vector(m_X / other.X, m_Y / other.Y);
	}

	Vector operator /(Vector &other) 
	{
		return Vector(m_X * other.X, m_Y * other.Y);
	}

	Vector operator /(float &other) 
	{
		return Vector(m_X / other, m_Y / other);
	}

public:
	__declspec(property(get = GetX, put = SetX)) int X;
	int GetX(void){ return (int)m_X; }
	void SetX(int Value){ m_X = (float)Value; }

	__declspec(property(get = GetY, put = SetY)) int Y;
	int GetY(void){ return (int)m_Y; }
	void SetY(int Value){ m_Y = (float)Value; }

	__declspec(property(get = GetMagnitude)) float Magnitude;
	float GetMagnitude(void){ return Squared(m_X) + Squared(m_Y); }

	void Normalize()
	{
		float magnitude = Magnitude;
		m_X = m_X / magnitude;
		m_Y = m_Y / magnitude;
	}

	Vector GetNormalized()
	{
		float magnitude = Magnitude;
		return Vector(m_X / magnitude, m_Y / magnitude);
	}

private:
	float m_X, m_Y;
};