#pragma once

#include <irrKlang.h>
#include <string>
#include "cSound.h"

using namespace irrklang;

class cAudio
{
public:
	cAudio(void);
	~cAudio(void);

public:
	cSound* FromFile(std::string FileName, bool IsLooping = false);
	cSound* Play(std::string FileName, bool IsLooping = false);

private:
	void Initialize_irrKlang(void);

private:
	ISoundEngine *m_Engine;
};
