#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "cTexture.h"
#include "cFont.h"
#include "cSound.h"

class cContentManager sealed
{
public:
	cContentManager() :
		m_RootPath("")
	{
	}
	cContentManager(std::string RootPath)
	{
		m_RootPath = RootPath;
	}

public:
	__declspec(property(get = GetRootPath, put = SetRootPath)) std::string RootPath;
	std::string GetRootPath(void) { return m_RootPath; }
	void SetRootPath(std::string Value) { m_RootPath = Value; }

	std::FILE* OpenFileStream(std::string FileName, std::string Mode);
	void DeleteFile(std::string FileName);
	cTexture* LoadTexture(std::string FileName, Color TransparentColor = Color(255, 255, 255));
	cFont* LoadFont(std::string FileName, int Size);


	/*template <class T> T Load(std::string FileName)
	{
		T temp;

		if (std::is_same<T, cSpriteBatch*>::value)
			temp = new cSpriteBatch(new SDL_Surface());
		
		return temp;
	}*/

private:
	std::string m_RootPath;
};