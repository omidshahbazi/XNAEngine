
#pragma once

#include <stdio.h>
#include <string>
#include "cTimer.h"

inline void Delay(int SleepTime)
{
	static cTimer* timer = new cTimer();
	//
	while (timer->GetMilliseconds() < SleepTime)
	{
		// Do nothing
	}
}

inline std::string IntToString(int Value)
{
	std::string temp = "";

	// Convert number to a char
	char buffer[256];
	_itoa_s(Value, buffer, 10);  // 10 is for decimal notation

	// Add the number to the string
	temp.append(buffer);
	
	return temp;
}