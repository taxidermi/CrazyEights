#include "Game.h"

#include "Utils/Utils.h"
#include "../template/Player.h"
#include "Bot.h"
#include "Round.h"
#include "Utils/Console.h"
#include "Utils/Input.h"

Game::~Game()
{
	ClearPlayers();
	if (round != nullptr)
		delete round;
}

std::vector<Player*> Game::GetPlayers()
{
	return players;
}

void Game::ClearPlayers()
{
	for (int i = static_cast<int>(players.size()) - 1; i > 0; i--)
		delete players[i];
	players.clear();
}

Round* Game::GetRound() const
{
	return this->round;
}

void Game::CreateNewRound()
{
	if (round != nullptr)
		delete round;
	round = new Round(players);
}

void Game::CreatePlayers(const int numOfPlayers)
{
	for (int i = 0; i < numOfPlayers; i++)
	{
		const std::string playerName = Utils::Input::AskUserForInput<std::string>("Enter Player " +
			std::to_string(i + 1) + "'s name: "); // i + 1 because i starts at 0
		players.push_back(new Player(playerName));
	}
	std::string output = "Created " + std::to_string(numOfPlayers) + " player";
	if (numOfPlayers > 1)
		output += 's';
	std::cout << output << "!\n";
}

void Game::CreateBotPlayers(const int numOfBots)
{
	for (int i = 0; i < numOfBots; i++)
		players.push_back(new Bot(std::string("Bot " + std::to_string(i + 1))));
	std::string output = "Created " + std::to_string(numOfBots) + " bot";
	if (numOfBots > 1)
		output += 's';
	std::cout << output << "!\n";
}

void Game::Setup()
{
	// Start the running loop
	bool runningLoop = true;
	while (runningLoop)
	{
		Utils::Console::Clear();
		Utils::Console::PrintTitle("Welcome to Crazy Eights!");
		Utils::SleepForMs(750);
		switch (Utils::Input::AskUserForInput("Select an option ([1] Play [2] Rules [3] Exit): ", 1, 3))
		{
			case 1: // Play
				StartGame();
				break;
			case 2: // Rules
				Utils::Console::PrintTitle("Rules", '-');
				Utils::Console::PrintAnimated("Short answer: it's like UNO but without the PVP or the fun cards");
				Utils::SleepForMs(1500);
				Utils::Console::PrintAnimated("The actual answer:");
				Utils::SleepForMs(300);
				Utils::Console::PrintAnimated("Each player starts with 5 cards, and the first player to empty "
								  "their hand wins!");
				Utils::Console::PrintAnimated("Each turn, the player must either place a card down that matches the "
								  "top card, or draw a card until they get a matching one.");
				Utils::Console::PrintAnimated("Eights are wild! They can be placed anytime, and once placed, "
								  "the player can choose the next matching suit.");
				Utils::SleepForS(5);
				std::cout << "\nEnter anything to continue...";
				Utils::Input::WaitForUserInput();
				break;
			case 3: // Exit
				std::cout << "Thank you for playing!\nExiting...\n";
				runningLoop = false;
				Utils::SleepForS(1);
				break;
			default:
				break;
		}
	}
}

void Game::StartGame()
{
	Utils::Console::Clear();
	Utils::Console::PrintTitle("SETUP PLAYERS", '=');
	// Start by creating the player's and bot's. Both are added to the players array.
	const int numOfPlayers = Utils::Input::AskUserForInput("Please enter the number of players (1-8): ",
		1, 8);
	CreatePlayers(numOfPlayers);
	// Ask to create any bots. If there is one player, force there to be a min of 1 bots
	const int numOfBots = Utils::Input::AskUserForInput("Please enter the number of bot players (" +
		std::string(numOfPlayers == 1 ? "1" : "0") + "-3): ",numOfPlayers == 1 ? 1 : 0, 3);
	CreateBotPlayers(numOfBots);

	// Game loop
	while (true)
	{
		// Create and start a new round, using the players (and bots) that were created above
		CreateNewRound();
		// Start the round
		round->StartRound();
		// Wait for round to finish (while loop)
		// Once round is finished, it gets deleted and this will continue
		// Print a round over title
		Utils::Console::PrintTitle("ROUND OVER", '=');
		// Ask user if they want to restart or exit
		const int userGameOption = Utils::Input::AskUserForInput("Please enter what you would like to do next ([1]: Restart, [2]: Menu): ", 1, 2);
		if (userGameOption == 1) // Restart
		{
			std::cout << "Restarting game...\n";
			// Since we are in the while loop, it will go back to the top and restart the game, no further action needed
		}
		else if (userGameOption == 2) // Exit
			break; // Break out of this while loop
	}

	std::cout << "Thank you for playing!\n... Going back to the menu\n";
	Utils::SleepForMs(750);
	// Clean up the game. Will loop back to the while runningLoop in Game::Setup()
	ClearPlayers();
}