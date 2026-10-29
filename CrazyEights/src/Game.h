#pragma once
#include <iostream>
#include <string>
#include <vector>

class Player;
class Round;

class Game
{
public:
	Game();

private:
	std::vector<Player*> players = {};
	Round* round = nullptr;

public:
	std::vector<Player*> GetPlayers();

	Round* GetRound();
	void CreateNewRound();

public:
	// Starts the game. Only to be called once from main().
	void Start();

	/**
	* @brief Creates a set number of players. Asks for the player's name when creating.
	*/
	void CreatePlayers(int numOfPlayers);
	/**
	* @brief Creates a set number of Bot players. Their name's are set to "Bot 1/2/3...".
	*/
	void CreateBotPlayers(int numOfBots);
};