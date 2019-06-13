#include "cGemsGame.h"

//
// Fun For XNA Source Code
// XNA written based on SDL API :D ;)
// http://code.google.com/p/monoxna/source/browse
// O.Shahabazi
//

int main(int arg, char** args)
{
	cGemsGame* game = new cGemsGame();

	game->Run(true, 1280, 720, "Gems");

	delete game;

	return 0;
}