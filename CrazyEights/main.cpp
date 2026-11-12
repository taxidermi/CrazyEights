#include "src/Game.h"
#include "src/Utils/Utils.h"

int main()
{
	// Seed random num generator at the start
	srand(time(nullptr));
	Game* game = new Game();
	game->Setup();
	return 0;
}
