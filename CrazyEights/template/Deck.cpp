#include "Deck.h"

#include <algorithm>
#include <ctime>
#include <random>

Deck::Deck()
{
	this->deck_vector = {};
	//this->FillDeck(); // Use Deck(true);
}

Deck::Deck(bool fillDeck)
{
	this->deck_vector = {};
	this->FillDeck();
}

int Deck::GetSize()
{
	return this->deck_vector.size();
}

bool Deck::IsEmpty()
{
	return this->deck_vector.empty();
}

void Deck::Shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(this->deck_vector.begin(), this->deck_vector.end(), g);
}

void Deck::Clear()
{
	this->deck_vector.clear();
}

void Deck::FillDeck()
{
	//Iterates through all 13 cards for each suit separately.
	for (int i = 1; i < 14; i++) {
		Card* n_card = new Card(i, "Clubs");
		this->deck_vector.push_back(n_card);
	}

	for (int i = 1; i < 14; i++) {
		Card* n_card = new Card(i, "Hearts");
		this->deck_vector.push_back(n_card);
	}

	for (int i = 1; i < 14; i++) {
		Card* n_card = new Card(i, "Diamonds");
		this->deck_vector.push_back(n_card);
	}

	for (int i = 1; i < 14; i++) {
		Card* n_card = new Card(i, "Spades");
		this->deck_vector.push_back(n_card);
	}

}

void Deck::AddCard(Card* new_card)
{
	this->deck_vector.push_back(new_card);
}

Card* Deck::PeekCard(int index)
{
	return this->deck_vector[index];
}

Card* Deck::PeekTopCard()
{
	int top_card_index = this->GetSize() - 1;
	return this->PeekCard(top_card_index);
}

Card* Deck::GetCard(int index)
{
	//Temporary variable must be created to return object after deleting card from vector.
	Card* card = this->deck_vector[index];
	this->deck_vector.erase(this->deck_vector.begin() + index);
	return card;
}

void Deck::RemoveCard(int index)
{
	this->deck_vector.erase(this->deck_vector.begin() + index);
}

Card* Deck::GetTopCard()
{
	int top_card_index = this->GetSize() - 1;
	return this->GetCard(top_card_index);
}