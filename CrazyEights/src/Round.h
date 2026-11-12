#pragma once
#include <vector>

class Deck;
class Player;
class Card;

enum class RoundState
{
	WAITING,
	STARTING,
	PLAYING,
	FINISHED,
	MAX
};

class Round
{
public:
	Round(std::vector<Player*> plrs);
	~Round();

	/**
	 * Clean up the round. Destroy's all decks and clears all references.
	 */
	void Cleanup();

private:
	std::vector<Player*> players = {};
	Deck* cardDeck = nullptr;
	Deck* discardPile = nullptr;
	RoundState currentRoundState = RoundState::WAITING;
	RoundState previousRoundState = RoundState::WAITING;

public:
	Deck* GetCardDeck() const;
	Deck* GetDiscardPile() const;

	RoundState GetCurrentRoundState() const;
	void SetCurrentRoundState(RoundState newState);
	RoundState GetPreviousRoundState() const;
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
	bool DiscardCard(Player* player, Card* card) const;

	void OnRoundFinished(Player* winningPlayer) const;

	/**
	 * Refill the card deck with the discard pile. Leaves the current top card alone.
	 */
	void RefillDeck() const;
};