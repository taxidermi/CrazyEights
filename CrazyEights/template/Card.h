#pragma once
#include <string>

/**
 * @brief Card class represents a single card when instantiated.
 */
class Card
{
public:
	static constexpr std::string CardSuits[4] = { "Clubs", "Diamonds", "Hearts", "Spades" };

private:
	/**
	 * Rank of card. Private, so must be accessed through getter and setter functions.
	 */
	int rank;
	/**
	 * Suit of card. Private, so must be accessed through getter and setter functions.
	 */
	std::string suit;
public:
	/**
	 * Constructor to create a card. Requires an initial Rank and Suit when created.
	 * \param init_rank An initial rank, as an integer (A=1, 2=2,... J=11, Q=12, K=13)
	 * \param init_suit An initial suit, given as a string
	 */
	Card(int init_rank, const std::string& init_suit);

	/**
	 * Get the card's rank.
	 * \return The rank of the card as an integer.
	 */
	int GetRank() const;

	/**
	 * Get the card's suit.
	 * \return The suit of the card as a string.
	 */
	std::string GetSuit();

	/**
	 * Set a new rank for the card.
	 * \param new_rank An integer of the new card rank.
	 */
	void SetRank(int new_rank);
	/**
	 * Set a new suit for the card.
	 *
	 * \param new_suit A string of the new card suit.
	 */
	void SetSuit(const std::string& new_suit);

	/**
	 * Get a string representation of the card.
	 *
	 * \return String representation of the card in the following format: "[rank] of [suit]".
	 */
	std::string ToString();

	/**
	* Check if another card matches this card (is it the same rank or suit)
	* \return True if the cards match one-another
	*/
	bool DoesCardMatch(Card* otherCard) const;

	/**
	 * Get the score value of this card.
	 * @return The score value of this card.
	 */
	int GetCardScore() const;

	/**
	* Create a random card and return it (Workshop session 5)
	*/
	static Card* CreateRandomCard();
};

