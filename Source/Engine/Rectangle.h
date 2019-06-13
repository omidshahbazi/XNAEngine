
#include "Size.h"
#include "Vector.h"
#include "Mathematics.h"

#pragma once

struct Rectangle
{
public:
	Rectangle() :
		m_X(0),
		m_Y(0),
		m_Width(0),
		m_Height(0)
	{
	}
	Rectangle(Vector Position, Vector Size) :
		m_X(Position.X),
		m_Y(Position.Y),
		m_Width(Size.X),
		m_Height(Size.Y)
	{
	}
	Rectangle(int X, int Y, int Width, int Height) :
		m_X(X),
		m_Y(Y),
		m_Width(Width),
		m_Height(Height)
	{
	}

public:
	__declspec(property(get = GetX, put = SetX)) int X;
	int GetX(void){ return m_X; }
	void SetX(int Value){ m_X = Value; }

	__declspec(property(get = GetY, put = SetY)) int Y;
	int GetY(void){ return m_Y; }
	void SetY(int Value){ m_Y = Value; }

	__declspec(property(get = GetWidth, put = SetWidth)) int Width;
	int GetWidth(void){ return m_Width; }
	void SetWidth(int Value){ m_Width = Value; }

	__declspec(property(get = GetHeight, put = SetHeight)) int Height;
	int GetHeight(void){ return m_Height; }
	void SetHeight(int Value){ m_Height = Value; }

	__declspec(property(get = GetCenter)) Vector Center;
	Vector GetCenter(void){ return Vector(m_X + (m_Width / 2.0f), m_Y + (m_Height / 2.0f)); }

	__declspec(property(get = GetTop)) int Top;
	int GetTop(void){ return m_Y; }

	__declspec(property(get = GetBottom)) int Bottom;
	int GetBottom(void){ return (m_Y + m_Height); }

	__declspec(property(get = GetLeft)) int Left;
	int GetLeft(void){ return m_X; }

	__declspec(property(get = GetRight)) int Right;
	int GetRight(void){ return (m_X + Width); }

	bool Contains(int X, int Y)
	{
		if (X >= m_X && X <= m_X + m_Width - 1)
		{
			// Check to see if the point's Y coordinate falls within the height of the 
			// rectangle. Remeber that the Y axis is reversed. 
			if (Y >= m_Y && Y <= m_Y + m_Height - 1)
			{
				return true;
			}
		}

		// The point is not within the rectangle 
		return false;
	}

	bool Contains(Vector Point)
	{
		return Contains(Point.X, Point.Y);
	}

	bool Contains(Rectangle Rectangle)
	{
		// top-left corner
		if (Contains(Rectangle.X, Rectangle.Y))
		{
			return true;
		}

		// top-right corner
		if (Contains(Rectangle.X + Rectangle.Width - 1, Rectangle.Y))
		{
			return true;
		}

		// bottom-right corner
		if (Contains(Rectangle.X + Rectangle.Width - 1, Rectangle.Y + Rectangle.Height - 1))
		{
			return true;
		}

		// bottom-left corner
		if (Contains(Rectangle.X, Rectangle.Y + Rectangle.Height - 1))
		{
			return true;
		}

		return false;
	}

	Vector GetBottomCenter(void)
	{
		return Vector(m_X + m_Width / 2.0f, (float)Bottom);
	}

	bool Intersects(Rectangle Rectangle)
    {
        if (m_X <= Rectangle.X)
        {
            if (Right > Rectangle.X)
            {
                if (m_Y < Rectangle.Y)
                {
                    if (Bottom > Rectangle.Y)
                        return true;
                }
                else
                {
					if (Rectangle.Bottom > m_Y)
                        return true;
                }
            }
        }
        else
        {
			if (Rectangle.Right > m_X)
            {
                if (m_Y < Rectangle.Y)
                {
                    if (Bottom > Rectangle.Y)
                        return true;
                }
                else
                {
					if (Rectangle.Bottom > m_Y)
                        return true;
                }
            }
        }

        return false;
    }

	Vector GetIntersectionDepth(Rectangle WithRectangle)
	{
		// Calculate half sizes.
		float halfWidthA = Width / 2.0f;
		float halfHeightA = Height / 2.0f;
		float halfWidthB = WithRectangle.Width / 2.0f;
		float halfHeightB = WithRectangle.Height / 2.0f;

		// Calculate centers.
		Vector centerA = Vector(Left + halfWidthA, Top + halfHeightA);
		Vector centerB = Vector(WithRectangle.Left + halfWidthB, WithRectangle.Top + halfHeightB);

		// Calculate current and minimum-non-intersecting distances between centers.
		int distanceX = centerA.X - centerB.X;
		int distanceY = centerA.Y - centerB.Y;
		float minDistanceX = halfWidthA + halfWidthB;
		float minDistanceY = halfHeightA + halfHeightB;

		// If we are not intersecting at all, return (0, 0).
		if (Abs((float)distanceX) >= minDistanceX || Abs((float)distanceY) >= minDistanceY)
			return Vector();

		// Calculate and return intersection depths.
		float depthX = distanceX > 0 ? minDistanceX - distanceX : -minDistanceX - distanceX;
		float depthY = distanceY > 0 ? minDistanceY - distanceY : -minDistanceY - distanceY;

		return Vector(depthX, depthY);
	}
private:
	int m_X, m_Y;
	int m_Width, m_Height;
};