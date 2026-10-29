#pragma once
#include <vector>

class Deck;
class Player;
class Card;

enum class RoundState
{
	STARTING,
	PLAYING,
	FINISHED,
	MAX
};

class Round
{
public:
	Round(std::vector<Player*> plrs);

private:
	std::vector<Player*> players = {};
	Deck* cardDeck = nullptr;
	Deck* discardPile = nullptr;
	RoundState currentRoundState = RoundState::MAX;
	RoundState previousRoundState = RoundState::MAX;

public:
	Deck* GetCardDeck();
	Deck* GetDiscardPile();

	RoundState GetCurrentRoundState();
	void SetCurrentRoundState(RoundState newState);
	RoundState GetPreviousRoundState();
	void SetPreviousRoundState(RoundState newState);
	
	/**
	* @brief Update the current round state. Updates both the Current and Previous round state variables.
	*/
	void UpdateRoundState(RoundState newState);

	/**
	* @brief Start the round. Creates the card and discard deck and gives each player the starting amount of cards before beginning.
	*/
	void StartRound();

	/**
	 * Function that removes and places a card onto the discard pile from a player.
	 * Checks if the player's hand is empty and they win after.
	 * @param player The player who is placing the card.
	 * @param card The card that is being placed.
	 * @return True if the card was successfully removed and placed.
	 */
	bool DiscardCard(Player* player, Card* card);
};