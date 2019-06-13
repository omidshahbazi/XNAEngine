#include "cFont.h"

void cFont::SetStyle(int Style)
{
	TTF_SetFontStyle(m_Font, Style);
}

Size cFont::GetSize(std::string Text)
{
	int w, h;

	TTF_SizeText(m_Font, Text.c_str(), &w, &h);

	return Size(w, h);
}

cFont* cFont::FromFile(std::string FileName, int Size)
{
	TTF_Init();

	return new cFont(TTF_OpenFont(FileName.c_str(), Size));
}