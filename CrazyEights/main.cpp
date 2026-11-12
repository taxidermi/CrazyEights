#include "src/Game.h"
#include "src/Utils.h"

int main()
{
	// Seed random num generator at the start
	srand(time(nullptr));
	// Start the running loop
	bool runningLoop = true;
	while (runningLoop)
	{
		Utils::ClearConsole();
		Utils::PrintTitle("Welcome to Crazy Eights!");
		Utils::SleepForMs(750);
		switch (Utils::AskUserForInput("Select an option ([1] Play [2] Rules [3] Exit): ", 1, 3))
		{
			case 1: // Play
			{
				Game game = Game();
				game.Start();
				break;
			}
			case 2: // Rules
			{
				Utils::PrintTitle("Rules", '-');
				std::cout << "Short answer: it's like UNO but without the PVP or the fun cards" << "\n";
				Utils::SleepForS(2);
				std::cout << "The actual answer:\n";
				Utils::SleepForMs(750);
				std::cout << "Each player starts with 5 cards, and the first player to empty their hand wins!\n"
				 "Each turn, the player must either place a card down that matches the top card, or draw a card until "
			     "they get a matching one.\n"
				 "Eights are wild! They can be placed anytime, and once placed, the player can choose the next matching suit.\n";
				Utils::SleepForS(5);
				std::cout << "\nEnter anything to continue...";
				Utils::WaitForUserInput();
				break;
			}
			case 3: // Exit
			{
				std::cout << "Exiting...\n";
				runningLoop = false;
				break;
			}
			default:
			{
				break;
			}
		}
	}
	
	return 0;
}
