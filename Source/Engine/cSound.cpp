#include "cSound.h"

cSound::cSound(ISound *Sound)
{
	m_Sound = Sound;
}

cSound::~cSound(void)
{
	delete m_Sound;
}

void cSound::Resume()
{
	m_Sound->setIsPaused(false);
}

void cSound::Pause()
{
	m_Sound->setIsPaused(true);
}

void cSound::Stop()
{
	m_Sound->stop();
}

void cSound::SetVolume(int Value)
{
	m_Sound->setVolume(Value / 100.0f);
}

void cSound::SetPan(int Value)
{
	m_Sound->setPan(Value / 100.0f);
}