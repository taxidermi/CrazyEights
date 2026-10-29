#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Card.h"

class Round;

enum class PlayerTurn
{
	DRAW,
	PLACE,
	MAX
};

enum class PlayerTurnResult
{
	PASS, // Pass to next player
	WIN, // Player won
	MAX
};

/**
 * @brief Player class represents a single player, either human or bot. Player has a name, a hand, and a score.
 * Class does not get input from terminal directly.
 */
class Player
{
private:
	/**
	 * Name of the player playing. Private, so must be accessed through indirectly through functions.
	 */
	std::string name;
	/**
	 * Player's hand. Stored as a vector of Card objects. Private, so must be accessed through indirectly through functions.
	 */
	std::vector<Card*> hand;
	/**
	 * Player's score. Changes to score must be made using the changeScoreBy, setScore, and getScore functions.
	 */
	int score;

public:
	/**
	 * Constructor to create a Player. Sets player name to "Unamed Player", hand starts empty, and score starts at 0.
	 */
	Player();
	/**
	 * Constructor to create a Player with a name. Hand starts empty, and score starts at 0.
	 */
	Player(std::string playerName);
	/**
	 * Gets the player's name.
	 * \return The name of the player.
	 */
	std::string GetName();

	/**
	 * Sets the player's name.
	 * \param new_name The new name of the player, as a string.
	 */
	void SetName(std::string new_name);
	/**
	 * Gets the number of cards in the player's hand.
	 * \return the size of hand.
	 */
	int GetHandSize();
	/**
	 * Gets the entire hand of the player.
	 * \return The vector containing Card objects.
	 */
	std::vector<Card*> GetHand();
	/**
	 * Clears the player's hand. Removes all cards from the player's hand permanently.
	 */
	void ClearHand();
	/**
	 * Returns true/false depending on whether there are any cards in the player's hand.
	 * \return boolean flag of if the player's hand is empty.
	 */
	bool IsEmpty();


	/**
	 * Returns the card at the given index. Important to note is the card will not be removed from the player's hand.
	 * \param index The index of the desired card.
	 * \return Card object of the card at the given index.
	 */
	Card* PeekCard(int index);
	/**
	 * Removes and returns the card at the given index. Important to note is the card will be removed from the player's hand.
	 * \param index The index of the desired card.
	 * \return Card object of the card at the given index.
	 */
	Card* GetCard(int index);
	/**
	 * Adds a new card to the player's hand. Card is placed at the back of the hand vector.
	 * \param new_card New card object to be added to the player's hand.
	 */
	void AddCard(Card* new_card);
	/**
	 * Removes the card at the given index from the player's hand.
	 * \param index The index of the card to be removed.
	 */
	void RemoveCard(int index);

	/**
	 * Removes the card from the player's hand, if found.
	 * \param cardToRemove The card pointer to remove
	 * \return True if the card was removed, false if it was not found/removed.
	 */
	bool RemoveCard(Card* cardToRemove);

	/**
	 * Calculates and returns the sum of all ranks from cards in the player's hand. Important to note is face cards are interpreted as 11, 12, and 13.
	 * \return Sum of all cards in player's hand.
	 */
	int SumHand();
	/**
	 * Iterates over all card objects in the player's hand and outputs each card's toString to terminal on separate lines.
	 */
	void OutputHand(bool includeCardIndex = false);

	/**
	 * Alter the player's score by given integer.
	 * \param toAdd Score to add to player's score. Score will be reduced if toAdd is negative.
	 */
	void ChangeScoreBy(int toAdd);
	/**
	 * Set a new score, overwriting the previous score.
	 * \param newScore New player score, given as an integer.
	 */
	void SetScore(int newScore);
	/**
	 * Gets the player's score.
	 * \return Player's score, given as an integer.
	 */
	int GetScore();

	/**
	* Check if the player can match the other card.
	* \return True if the player has a card that can match the other card.
	*/
	bool CanPlayerMatchCard(Card* otherCard);

	/**
	 * Get all the cards that the player can match with the passed other card.
	 * @param otherCard The other card to get all the cards the player can match with.
	 * @return Vector of cards that can match the other card.
	 */
	std::vector<Card*> GetMatchableCards(Card* otherCard);

	/**
	* Ask this player what they want to do, giving them the list of options to do.
	* \param topCard The card that is on top of the discard pile, which the player will need to match.
	*/
	virtual PlayerTurn AskPlayerForTurn(Card* topCard);

	/**
	 * Handle this player's turn. Gives the player turn options, waits for input and then performs the turn action.
	 * @param round Reference to the current round object.
	 * @return
	 */
	virtual PlayerTurnResult HandlePlayerTurn(Round* round);
};

