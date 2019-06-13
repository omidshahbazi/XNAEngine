#include "cContentManager.h"

std::FILE* cContentManager::OpenFileStream(std::string FileName, std::string Mode)
{
	std::FILE* file;
	
	fopen_s(&file, (m_RootPath + FileName).c_str(), Mode.c_str());

	return file;
}

void cContentManager::DeleteFile(std::string FileName)
{
	remove((m_RootPath + FileName).c_str());
}

cTexture* cContentManager::LoadTexture(std::string FileName, Color TransparentColor)
{
	return cTexture::FromFile(m_RootPath + FileName, TransparentColor);
}

cFont* cContentManager::LoadFont(std::string FileName, int Size)
{
	return cFont::FromFile(m_RootPath + FileName, Size);
}