#include "Game.h"

#include "Utils.h"
#include "../template/Player.h"
#include "Bot.h"
#include "Round.h"

Game::Game()
{

}

std::vector<Player*> Game::GetPlayers()
{
	return players;
}

Round* Game::GetRound()
{
	return this->round;
}

void Game::CreateNewRound()
{
	if (round != nullptr)
		delete round;
	round = new Round(players);
}

void Game::CreatePlayers(int numOfPlayers)
{
	for (int i = 0; i < numOfPlayers; i++)
	{
		std::string playerName = "Player " + std::to_string(i + 1); // + 1 because i starts at 0
		playerName = Utils::AskUserForInput<std::string>("Enter " + playerName + "'s name: ");
		players.push_back(new Player(playerName));
	}
	std::cout << "Created " << players.size() << " players!\n";
}

void Game::CreateBotPlayers(int numOfBots)
{
	/*if (numOfBots == 0)
		return;*/
	for (int i = 0; i < numOfBots; i++)
		players.push_back(new Bot(std::string("Bot " + i)));
	std::cout << "Created " << numOfBots << " bots!\n";
}

void Game::Start()
{
	// Start by creating the player's and bot's. Both are added to the players array.
	const int numOfPlayers = Utils::AskUserForInput("Please enter the number of players (1-8): ",
		1, 8);
	CreatePlayers(numOfPlayers);
	// Ask to create any bots. If there is one player, force there to be a min of 1 bots
	const int numOfBots = Utils::AskUserForInput("Please enter the number of bot players (" +
		std::string(numOfPlayers == 1 ? "1" : "0") + "-3): ",numOfPlayers == 1 ? 1 : 0, 3);
	CreateBotPlayers(numOfBots);

	// Game loop
	while (true)
	{
		// Create and start a new round, using the players (and bots) that were created above
		CreateNewRound();
		if (round == nullptr)
			break;
		// Start the round
		round->StartRound();
		// Wait for round to finish (while loop)
		// Ask user if they want to restart or exit
		int userGameOption = Utils::AskUserForInput("Please enter what you would like to do next (0 = restart, 1 = exit): ", 0, 1);
		if (userGameOption == 0) // Restart
		{
			std::cout << "Restarting game...\n";
			// Since we are in the while loop, it will go back to the top and restart the game, no further action needed
		}
		else if (userGameOption == 1) // Exit
			break; // Break out of this while loop
	}

	std::cout << "Thank you for playing!\nExiting game...\n";
	// Back to main()
}