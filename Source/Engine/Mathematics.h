//////////////////////////////////////////////////////////////////////////////////
// Project: SDL Game Engine
//////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <time.h>
#include <math.h>
#include <stdlib.h>

inline int GetRandomInteger(int start, int end)
{
	// Seed the random number generator if it hasn't been seeded already 
	static bool seeded = false;
	if (!seeded)
	{
		srand((unsigned)time(0));
		seeded = true;
	}

	// Size of the range 
	int size = end - start + 1;

	// Get a random number between 0 and size 
	int num = rand() % size;

	// Add start to get the random number into the proper range 
	return num + start;
}

inline float Min(float Value1, float Value2)
{
	if (Value1 < Value2)
		return Value1;

	return Value2;
}

inline float Max(float Value1, float Value2)
{
	if (Value1 > Value2)
		return Value1;

	return Value2;
}

inline float Clamp(float Value, float MinValue, float MaxValue)
{
	// First we check to see if we're greater than the max
	Value = (Value > MaxValue) ? MaxValue : Value;

	// Then we check to see if we're less than the min.
	Value = (Value < MinValue) ? MinValue : Value;

	// There's no check to see if min > max.
	return Value;
}

inline float Abs(float Value)
{
	if (Value < 0)
		return -Value;
	
	return Value;
}

inline float Power(float X, float Y)
{
	for (int i = 1; i <= Y; i++)
		X *= X;

	return X;
}

inline float Squared(float X)
{
	return Power(X, 2);
}

inline float SQRT(float X)
{
	return sqrt(X);
}

inline int Round(float Value)
{
	int floor = (int)Value;
	int ceiling  = ((int)Value == Value) ? (int)Value : (int)Value + 1;

	if (Value - floor < ceiling - Value)
		return floor;

	return ceiling;
}

inline int Ceiling(float Value)
{
	if ((int)Value == Value)
		return (int)Value;

	return (int)Value + 1;
}

inline int Floor(float Value)
{
	return (int)Value;
}

inline double Sin(double Value)
{
	return sin(Value);
}

inline float ToDegrees(float Radians)
{
    // This method uses double precission internally,
    // though it returns single float
    // Factor = 180 / pi
    return (float)(Radians * 57.295779513082320876798154814105);
}
        
inline float ToRadians(float Degrees)
{
    // This method uses double precission internally,
    // though it returns single float
    // Factor = pi / 180
    return (float)(Degrees * 0.017453292519943295769236907684886);
}

inline float WrapAngle(float Angle)
{
    //angle = (float)Math.IEEERemainder((double)angle, 6.2831854820251465); //2xPi precission is double
    //if (angle <= -3.141593f)
    //{
    //    angle += 6.283185f;
    //    return angle;
    //}
    //if (angle > 3.141593f)
    //{
    //    angle -= 6.283185f;
    //}
    //return angle;

	return 0;
}
