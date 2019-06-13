#pragma once

#include "Engine\cTexture.h"

enum TileCollision
{
	TileCollision_Passable = 0,
	TileCollision_Impassable = 1,
	TileCollision_Platform = 2
};

struct Tile
{
public:
	Tile() :
		Texture(0),
		Collision(TileCollision_Passable)
	{}
	Tile(cTexture* Texture, TileCollision Collision) :
		Texture(Texture),
		Collision(Collision)
	{}

public:
	static const int Width = 64;
	static const int Height = 48;

	cTexture* Texture;
	TileCollision Collision;
};