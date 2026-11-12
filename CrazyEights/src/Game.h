#pragma once
#include <vector>

class Player;
class Round;

class Game
{
public:
	~Game();

private:
	std::vector<Player*> players = {};
	Round* round = nullptr;

	/**
	 * Create a new round object. Delete's the previous round object if it exists.
	 */
	void CreateNewRound();

	/**
	 * Starts a game. Creates the players and sets up a round.
	 */
	void StartGame();

	/**
	* Creates a set number of players. Asks for the player's name when creating.
	*/
	void CreatePlayers(int numOfPlayers);
	/**
	* Creates a set number of Bot players. Their name's are set to "Bot 1/2/3...".
	*/
	void CreateBotPlayers(int numOfBots);

public:
	/**
	 * Sets up the game, starting the running loop and displaying the main menu. Called from the constructor
	 */
	void Setup();

	/**
	 * @return The array of players from this game class, as pointers.
	 */
	std::vector<Player*> GetPlayers();

	/**
	 * Delete and clear the player's list.
	 */
	void ClearPlayers();

	Round* GetRound() const;


};