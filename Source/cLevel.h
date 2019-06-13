#pragma once

#include "Tile.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cGem.h"
#include "Engine\cGameTime.h"
#include "Engine\cSpriteBatch.h"
#include "Engine\Vector.h"
#include "Engine\cContentManager.h"
#include "Engine\cInput.h"
#include "Engine\Mathematics.h"
#include "Engine\General.h"

#include <fstream>
#include <vector>

class cLevel
{
public:
	static const std::string SaveFilePath;

private:
	static const int PointsPerSecond = 5;

public:
	cLevel(int LevelIndex, cContentManager* Content, cAudio *Audio, cInput *Input);
	~cLevel(void);

public:
	__declspec(property(get = GetScore)) int Score;
	int GetScore(void) { return m_Score; }

	__declspec(property(get = GetTimeRemaining)) int TimeRemaining;
	int GetTimeRemaining(void) { return m_TimeRemaining; }
	
	__declspec(property(get = GetHeight)) int Height;
	int GetHeight(void) { return m_TilesArray.size(); }
	
	__declspec(property(get = GetWidth)) int Width;
	int GetWidth(void) { return m_TilesArray[0].size(); }
	
	__declspec(property(get = GetPlayer)) cPlayer* Player;
	cPlayer* GetPlayer(void) { return m_Player; }
	
	__declspec(property(get = GetReachedExit)) bool ReachedExit;
	bool GetReachedExit(void) { return m_ReachedExit; }

	void Update(cGameTime* GameTime);
	void Draw(cGameTime* GameTime, cSpriteBatch* SpriteBatch);
	void StartNewLife(void);

private:
	void UpdateGems(cGameTime *GameTime);
	void UpdateEnemies(cGameTime *GameTime);
	Rectangle GetBounds(int X, int Y);
	void LoadTiles(int LoadIndex);
	Tile LoadTile(char TitleType, int x, int y);
	Tile LoadTile(std::string Name, TileCollision Collision);
	Tile LoadVarietyTile(std::string BaseName, int VariationCount, TileCollision Collision);
	Tile LoadStartTile(int X, int Y);
	Tile LoadExitTile(int X, int Y);
	Tile LoadEnemyTile(int X, int Y, std::string spriteSet);
	Tile LoadGemTile(int X, int Y);
	void DrawTiles(cSpriteBatch* SpriteBatch);
	void DrawEnemies(cGameTime* GameTime, cSpriteBatch* SpriteBatch);
	void OnPlayerKilled(cEnemy *KilledBy);
	void OnEnemyKilled(cEnemy *Enemy);
	void OnExitReached(void);
	void OnGemCollected(cGem Gem);
	void SaveCurrentState(void);

private:
	std::vector<std::vector<Tile>> m_TilesArray;
	std::vector<cGem*> m_GemsArray;
	std::vector<cGem*>::iterator m_GemsIterator;
	std::vector<cEnemy*> m_EnemiesArray;
	std::vector<cTexture*> m_LayersArray;
	cContentManager *m_Content;
	cPlayer* m_Player;
	cAudio *m_Audio;
	cInput* m_Input;
	Vector m_Start;
	Vector m_Exit;
	int m_LevelIndex;
	int m_Score;
	int m_TimeRemaining;
	bool m_ReachedExit;
};