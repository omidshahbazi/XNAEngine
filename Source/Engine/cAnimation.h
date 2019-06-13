#pragma once

#include "Engine\cTexture.h"

class cAnimation
{
public:
	cAnimation(void);
	cAnimation(cTexture* Texture, float FrameTime, bool IsLooping)
	{
		m_Texture = Texture;
		m_FrameTime = FrameTime;
		m_IsLooping = IsLooping;
	}
	~cAnimation(void)
	{
		if (m_Texture)
			delete m_Texture;
	}
	
public:
	__declspec(property(get = GetTexture)) cTexture* Texture;
	cTexture* GetTexture(void) { return m_Texture; }
	
	__declspec(property(get = GetFrameTime)) float FrameTime;
	float GetFrameTime(void) { return m_FrameTime; }
	
	__declspec(property(get = GetIsLooping)) bool IsLooping;
	bool GetIsLooping(void) { return m_IsLooping; }

	__declspec(property(get = GetFrameCount)) int FrameCount;
	int GetFrameCount(void) { return (m_Texture->Width / m_Texture->Height); }

	__declspec(property(get = GetFrameWidth)) int FrameWidth;
	int GetFrameWidth(void) 
	{
		return (m_Texture->Height);

		// We must return below value for this method, but in cycles sprites we have for example : 10 * (96 * 96)
		//return (m_Texture->Width);
	}
	
	__declspec(property(get = GetFrameHeight)) int FrameHeight;
	int GetFrameHeight(void) { return (m_Texture->Height); }

private:
	cTexture* m_Texture;
	float m_FrameTime;
	bool m_IsLooping;

};
