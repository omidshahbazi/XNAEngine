#pragma once

#include <irrKlang.h>
#include <string>

using namespace irrklang;

class cSound
{
public:
	cSound(ISound *Sound);
	~cSound(void);

public:
	__declspec(property(get = GetIsLooped, put = SetIsLooped)) bool IsLooped;
	bool GetIsLooped(void) { return m_Sound->isLooped(); }
	void SetIsLooped(bool Value) { m_Sound->setIsLooped(Value); }

	void Resume(void);
	void Pause(void);
	void Stop(void);
	void SetVolume(int Value);
	void SetPan(int Value);

private:
	ISound *m_Sound;
};
