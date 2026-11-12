#include "Game.h"

#include "Utils.h"
#include "../template/Player.h"
#include "Bot.h"
#include "Round.h"

std::vector<Player*> Game::GetPlayers()
{
	return players;
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
		const std::string playerName = Utils::AskUserForInput<std::string>("Enter Player " +
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

void Game::Start()
{
	Utils::PrintTitle("SETUP PLAYERS", '=');
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
		// Start the round
		round->StartRound();
		// Wait for round to finish (while loop)
		// Once round is finished, this will continue here
		// Print a round over title
		Utils::PrintTitle("ROUND OVER", '=');
		// Ask user if they want to restart or exit
		const int userGameOption = Utils::AskUserForInput("Please enter what you would like to do next ([1]: Restart, [2]: Exit): ", 1, 2);
		if (userGameOption == 1) // Restart
		{
			std::cout << "Restarting game...\n";
			// Since we are in the while loop, it will go back to the top and restart the game, no further action needed
		}
		else if (userGameOption == 2) // Exit
			break; // Break out of this while loop
	}

	std::cout << "Thank you for playing!\nExiting game...\n";
	// Back to main()
}