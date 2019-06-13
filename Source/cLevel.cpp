#include "cLevel.h"

const std::string cLevel::SaveFilePath = "Saves\\Level.dat";

cLevel::cLevel(int LevelIndex, cContentManager* Content, cAudio *Audio, cInput *Input)
{
	m_Content = Content;
	m_Audio = Audio;
	m_Input = Input;
	m_Score = 0;
	m_ReachedExit = false;

	LoadTiles(LevelIndex);

	m_LayersArray.push_back(m_Content->LoadTexture("Backgrounds\\Layer" + IntToString(GetRandomInteger(0, 26)) + ".jpg"));

	m_TimeRemaining = 1000;
}

cLevel::~cLevel(void)
{

}

Rectangle cLevel::GetBounds(int X, int Y)
{
	return Rectangle(X * Tile::Width, Y * Tile::Height, Tile::Width, Tile::Height);
}

void cLevel::Update(cGameTime* GameTime)
{
	// Pause while the player is dead or time is expired.
	if (!m_Player->IsAlive || m_TimeRemaining == 0)
	{
		// Still want to perform physics on the player.
		m_Player->ApplyPhysics(GameTime);
	}
	else if (m_ReachedExit)
	{
		// Animate the time being converted into points.
		int seconds = (int)Round(GameTime->ElapsedGameTime / 1000.0f * 100.0f);
		seconds = (int)Min((float)seconds, (float)Ceiling((float)m_TimeRemaining));
		m_TimeRemaining -= seconds;
		m_Score += m_TimeRemaining * PointsPerSecond;
		m_TimeRemaining = 0;
	}
	else
	{
		m_TimeRemaining -= (GameTime->ElapsedGameTime / 1000.0f);

		m_Player->Update(GameTime);

		UpdateGems(GameTime);

		// Falling off the bottom of the level kills the player.
		if (m_Player->BoundingRectangle.Top >= Height * Tile::Height)
			OnPlayerKilled(NULL);

		UpdateEnemies(GameTime);

		// The player has reached the exit if they are standing on the ground and
		// his bounding rectangle contains the center of the exit tile. They can only
		// exit when they have collected all of the gems.
		if (m_Player->IsAlive &&
			m_Player->IsOnGround &&
			m_Player->BoundingRectangle.Contains(m_Exit) &&
			m_Score >= 250)
		{
			OnExitReached();
		}
	}

	// Clamp the time remaining at zero.
	if (m_TimeRemaining < 0)
		m_TimeRemaining = 0;
}

void cLevel::UpdateGems(cGameTime *GameTime)
{
	m_GemsIterator = m_GemsArray.begin();

	while (m_GemsIterator != m_GemsArray.end())
    {
        cGem *gem = *m_GemsIterator;

        gem->Update(GameTime);

		if (gem->BoundingCircle.Intersects(m_Player->BoundingRectangle))
        {
			if (m_GemsIterator == m_GemsArray.begin())
				m_GemsArray.erase(m_GemsIterator);
			else
				m_GemsArray.erase(m_GemsIterator--);

            OnGemCollected(*gem);

			m_GemsIterator = m_GemsArray.begin();
        }
		else
			m_GemsIterator++;
    }
}

void cLevel::UpdateEnemies(cGameTime *GameTime)
{
	std::vector<cEnemy*>::iterator iterator = m_EnemiesArray.begin();

	while (iterator != m_EnemiesArray.end())
    {
        cEnemy *enemy = *iterator;

		enemy->Update(GameTime);

		Rectangle rect = m_Player->BoundingRectangle;
		rect.Width += 30;
		
		if (enemy->CanErase)
        {
			m_EnemiesArray.erase(iterator);
			break;
        }
		else
		{
			if (m_Player->IsKilling && enemy->BoundingRectangle.Intersects(rect))
			{
				OnEnemyKilled(enemy);
			}
			else if (enemy->IsAlive && enemy->BoundingRectangle.Intersects(m_Player->BoundingRectangle))
			{
				OnPlayerKilled(enemy);
			}

			iterator++;
		}
    }
}

void cLevel::Draw(cGameTime* GameTime, cSpriteBatch* SpriteBatch)
{
	for (int i = 0; i < m_LayersArray.size(); i++)
		SpriteBatch->Draw(m_LayersArray[i], Rectangle(0, 0, 1280, 720), Vector(0));

	DrawTiles(SpriteBatch);

	for (int i = 0; i < m_GemsArray.size(); i++)
        m_GemsArray[i]->Draw(GameTime, SpriteBatch);
	
	m_Player->Draw(GameTime, SpriteBatch);

	DrawEnemies(GameTime, SpriteBatch);
}

void cLevel::DrawTiles(cSpriteBatch* SpriteBatch)
{
    for (int y = 0; y < Height; ++y)
    {
        for (int x = 0; x < Width; ++x)
        {
            cTexture* texture = m_TilesArray[y][x].Texture;

            if (texture)
            {
                // Draw it in screen space.
				Vector position = Vector((float)x, (float)y) * Vector((float)Tile::Width, (float)Tile::Height);

				SpriteBatch->Draw(texture, Rectangle(0, 0, Tile::Width, Tile::Height), position);
            }
        }
    }
}

void cLevel::DrawEnemies(cGameTime* GameTime, cSpriteBatch* SpriteBatch)
{
	for (int x = 0; x < m_EnemiesArray.size(); ++x)
		m_EnemiesArray[x]->Draw(GameTime, SpriteBatch);
}

void cLevel::LoadTiles(int LoadIndex)
{
	m_LevelIndex = LoadIndex;

	std::vector<std::string> lines;
	
	std::FILE* file = m_Content->OpenFileStream("Levels\\" + IntToString(m_LevelIndex) + ".map", "r");

	if (file != NULL)
	{
		while (true)
		{
			char data[100];

			fgets(data, 100, file);

			lines.push_back(std::string(data));

			if (file->_cnt == 0) break;
		}
	
		for (int y = 0; y < lines.size(); y++)
		{
			std::string line = lines[y];

			std::vector<Tile> list;

			for (int x = 0; x < line.size() - 1; x++) 
			{
				const Tile tile = LoadTile(line[x], x, y);
				list.push_back(tile);
			}
			
			m_TilesArray.push_back(list);
		}

		m_Player = new cPlayer(m_TilesArray, m_Input, m_Content, m_Audio, m_Start);

		for (int x = 0; x < m_EnemiesArray.size(); ++x)
			m_EnemiesArray[x]->SetTiles(m_TilesArray);
	}
	else
		throw "Level file not found!";
}

Tile cLevel::LoadTile(char TitleType, int X, int Y)
{
	switch (TitleType)
    {
        // Blank space
        case '.':
            return Tile(NULL, TileCollision_Passable);

        // Exit
        case 'X':
            return LoadExitTile(X, Y);

        // Gem
        case 'G':
            return LoadGemTile(X, Y);

        // Floating platform
        case '-':
            return LoadTile("Platform", TileCollision_Platform);

        // Various enemies
        case 'A':
			return LoadEnemyTile(X, Y, "MonsterA");
        case 'B':
			return LoadEnemyTile(X, Y, "MonsterB");
        case 'C':
			return LoadEnemyTile(X, Y, "MonsterC");
        case 'D':
			return LoadEnemyTile(X, Y, "MonsterD");

        // Platform block
        case '~':
            return LoadVarietyTile("BlockB", 1, TileCollision_Platform);

        // Passable block
        case ':':
            return LoadVarietyTile("BlockB", 1, TileCollision_Passable);

        // Player 1 start point
        case '1':
            return LoadStartTile(X, Y);

        // Impassable block
        case '#':
            return LoadVarietyTile("BlockA", 6, TileCollision_Impassable);
    }

	return Tile();
}

Tile cLevel::LoadTile(std::string Name, TileCollision Collision)
{
	return Tile(m_Content->LoadTexture("Tiles\\" + Name + ".bmp", Color(0, 0, 0)), Collision);
}

Tile cLevel::LoadVarietyTile(std::string BaseName, int VariationCount, TileCollision Collision)
{
	return LoadTile(BaseName + IntToString(GetRandomInteger(0, VariationCount)), Collision);
}

Tile cLevel::LoadStartTile(int X, int Y)
{
	m_Start = GetBounds(X, Y).GetBottomCenter();

    return Tile(NULL, TileCollision_Passable);
}

Tile cLevel::LoadExitTile(int X, int Y)
{
    m_Exit = GetBounds(X, Y).Center;

    return LoadTile("Exit", TileCollision_Passable);
}

Tile cLevel::LoadEnemyTile(int X, int Y, std::string SpriteSet)
{
    Vector position = GetBounds(X, Y).GetBottomCenter();

	m_EnemiesArray.push_back(new cEnemy(m_Content, m_Audio, position, SpriteSet));

    return Tile(NULL, TileCollision_Passable);
}

Tile cLevel::LoadGemTile(int X, int Y)
{
    Vector position = GetBounds(X, Y).Center;

	m_GemsArray.push_back(new cGem(m_Content, m_Audio, position));

    return Tile(NULL, TileCollision_Passable);
}

void cLevel::OnPlayerKilled(cEnemy *KilledBy)
{
	for (int x = 0; x < m_EnemiesArray.size(); ++x)
        m_EnemiesArray[x]->OnIdleAnimation();

	m_Player->OnKilled(KilledBy);
}

void cLevel::OnEnemyKilled(cEnemy *Enemy)
{
	m_Score += cEnemy::PointValue;

	Enemy->OnKilled();
}

void cLevel::OnExitReached(void)
{
	SaveCurrentState();

    m_Player->OnReachedExit();

    m_ReachedExit = true;
}

void cLevel::StartNewLife(void)
{
    m_Player->Reset(m_Start);
}

void cLevel::OnGemCollected(cGem Gem)
{
	m_Score += cGem::PointValue;

    Gem.OnCollected();
}

void cLevel::SaveCurrentState()
{
	std::FILE *file = m_Content->OpenFileStream(cLevel::SaveFilePath, "r");

	if (file != NULL)
	{
		fclose(file);

		m_Content->DeleteFile(cLevel::SaveFilePath);
	}

	file = m_Content->OpenFileStream(cLevel::SaveFilePath, "w");

	fputs(IntToString(m_LevelIndex).c_str(), file);

	fclose(file);
}