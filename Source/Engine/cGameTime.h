
#include "cTimer.h"

#pragma once

class cGameTime
{
public:
	cGameTime(void)
	{
		m_ElapsedGameTime = 0;
		m_ElapsedRealTime = 0;
		m_TotalGameTime = 0;
		m_TotalRealTime = 0;
		m_IsRunningSlowly = false;
		m_Timer = new cTimer();
	}
    
	// All values are in Millisecond.
	cGameTime(int TotalRealTime, int ElapsedRealTime, int TotalGameTime, int ElapsedGameTime) :
		m_TotalRealTime(TotalRealTime),
		m_ElapsedRealTime(ElapsedRealTime),
		m_TotalGameTime(TotalGameTime),
		m_ElapsedGameTime(ElapsedGameTime)
	{
		m_Timer = new cTimer();
	}

	~cGameTime(void)
	{
	}

public:
	int GetSeconds(void)
	{
		return m_Timer->GetSeconds();
	}

	int GetMilliseconds(void)
	{
		return m_Timer->GetMilliseconds();
	}

public:
	__declspec(property(get = GetElapsedGameTime, put = SetElapsedGameTime)) int ElapsedGameTime;
	int GetElapsedGameTime(void) { return m_ElapsedGameTime; }
	void SetElapsedGameTime(int x) { m_ElapsedGameTime = x; }

	__declspec(property(get = GetElapsedRealTime, put = SetElapsedRealTime)) int ElapsedRealTime;
	int GetElapsedRealTime(void) { return m_ElapsedRealTime; }
	void SetElapsedRealTime(int x) { m_ElapsedRealTime = x; }
	
	__declspec(property(get = GetTotalGameTime, put = SetTotalGameTime)) int TotalGameTime;
	int GetTotalGameTime(void) { return m_TotalGameTime; }
	void SetTotalGameTime(int x) { m_TotalGameTime = x; }
	
	__declspec(property(get = GetTotalRealTime, put = SetTotalRealTime)) int TotalRealTime;
	int GetTotalRealTime(void) { return m_TotalRealTime; }
	void SetTotalRealTime(int x) { m_TotalRealTime = x; }
	
	__declspec(property(get = GetIsRunningSlowly, put = SetIsRunningSlowly)) bool IsRunningSlowly;
	bool GetIsRunningSlowly(void) { return m_IsRunningSlowly; }
	void SetIsRunningSlowly(bool value) { m_IsRunningSlowly = value; }

private:
	int m_ElapsedGameTime;
	int m_ElapsedRealTime;
	int m_TotalGameTime;
	int m_TotalRealTime;
	bool m_IsRunningSlowly;

	cTimer* m_Timer;
};

