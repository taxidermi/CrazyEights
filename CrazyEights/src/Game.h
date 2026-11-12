#pragma once
#include <vector>

class Player;
class Round;

class Game
{
public:
	Game() = default;

private:
	std::vector<Player*> players = {};
	Round* round = nullptr;

public:
	/**
	 * @return The array of players from this game class, as pointers.
	 */
	std::vector<Player*> GetPlayers();

	Round* GetRound() const;

	/**
	 * Create a new round object. Delete's the previous round object if it exists.
	 */
	void CreateNewRound();

	/**
	 * Starts the game. Only to be called once from main().
	 */
	void Start();

	/**
	* Creates a set number of players. Asks for the player's name when creating.
	*/
	void CreatePlayers(int numOfPlayers);
	/**
	* Creates a set number of Bot players. Their name's are set to "Bot 1/2/3...".
	*/
	void CreateBotPlayers(int numOfBots);
};