#pragma once

struct Size
{
public:
	Size() :
		Width(0),
		Height(0)
		{}

	Size(int width, int height) :
		Width(width),
		Height(height)
	{}

public:
	int Width, Height;
};