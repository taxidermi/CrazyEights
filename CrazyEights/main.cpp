#include "src/Game.h"
#include "src/Utils.h"

int main()
{
	srand(time(nullptr));

	Utils::ClearConsole();
	Utils::PrintTitle("Crazy Eights", '-');
	Utils::SleepForMs(150);

	const int userMenuOption = Utils::AskUserForInput("Select an option ([1] Play [2] Exit): ", 1, 2);
	if (userMenuOption == 1)
	{
		Game game = Game();
		game.Start();
	}
	else
		std::cout << "Exiting...\n";
	
	return 0;
}
