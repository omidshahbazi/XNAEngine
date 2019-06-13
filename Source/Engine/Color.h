#pragma once

struct Color
{
public:
	Color() :
		m_Red(0),
		m_Green(0),
		m_Blue(0)
	{}
	Color(int R, int G, int B) :
		m_Red(R),
		m_Green(G),
		m_Blue(B)
	{}

public:
	__declspec(property(get = GetRed, put = SetRed)) int Red;
	int GetRed(void) { return m_Red; }
	void SetRed(int Value) { m_Red = Value; }
	
	__declspec(property(get = GetGreen, put = SetGreen)) int Green;
	int GetGreen(void) { return m_Green; }
	void SetGreen(int Value) { m_Green = Value; }
	
	__declspec(property(get = GetBlue, put = SetBlue)) int Blue;
	int GetBlue(void) { return m_Blue; }
	void SetBlue(int Value) { m_Blue = Value; }

private:
	int m_Red, m_Green, m_Blue;
};