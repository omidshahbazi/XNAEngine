#include "cAudio.h"

cAudio::cAudio()
{
	Initialize_irrKlang();
}

cAudio::~cAudio(void)
{
	m_Engine->drop();
}

void cAudio::Initialize_irrKlang()
{
	// start up the engine
	m_Engine = createIrrKlangDevice();
}

cSound* cAudio::FromFile(std::string FileName, bool IsLooping)
{
	cSound *sound = Play(FileName, IsLooping);
	sound->Pause();
	return sound;
}

cSound* cAudio::Play(std::string FileName, bool IsLooping)
{
	return new cSound(m_Engine->play2D(FileName.c_str(), IsLooping, false, true)); 
}