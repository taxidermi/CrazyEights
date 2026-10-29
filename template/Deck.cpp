#include "Deck.h"

#include <algorithm>
#include <ctime>
#include <random>

Deck::Deck()
{
	this->deck_vector = {};
	this->fillDeck();
}

int Deck::getSize()
{
	return this->deck_vector.size();
}

bool Deck::isEmpty()
{
	return this->deck_vector.empty();
}

void Deck::shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(this->deck_vector.begin(), this->deck_vector.end(), g);
}

void Deck::clear()
{
	this->deck_vector.clear();
}

void Deck::fillDeck()
{
	//Iterates through all 13 cards for each suit separately.
	for (int i = 1; i < 14; i++) {
		Card n_card = Card(i, "Clubs");
		this->deck_vector.push_back(n_card);
	}

	for (int i = 1; i < 14; i++) {
		Card n_card = Card(i, "Hearts");
		this->deck_vector.push_back(n_card);
	}

	for (int i = 1; i < 14; i++) {
		Card n_card = Card(i, "Diamonds");
		this->deck_vector.push_back(n_card);
	}

	for (int i = 1; i < 14; i++) {
		Card n_card = Card(i, "Spades");
		this->deck_vector.push_back(n_card);
	}

}

void Deck::addCard(Card new_card)
{
	this->deck_vector.push_back(new_card);
}

Card Deck::peekCard(int index)
{
	return this->deck_vector[index];
}

Card Deck::peekTopCard()
{
	int top_card_index = this->getSize() - 1;
	return this->peekCard(top_card_index);
}

Card Deck::getCard(int index)
{
	//Temporary variable must be created to return object after deleting card from vector.
	Card tmp_card = this->deck_vector[index];
	this->deck_vector.erase(this->deck_vector.begin() + index);
	return tmp_card;
}

void Deck::removeCard(int index)
{
	this->deck_vector.erase(this->deck_vector.begin() + index);
}

Card Deck::getTopCard()
{
	int top_card_index = this->getSize() - 1;
	return this->getCard(top_card_index);
}