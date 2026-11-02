#include "src/Game.h"

int main()
{
	srand(time(nullptr));
	Game game = Game();
	game.Start();
	return 0;
}
