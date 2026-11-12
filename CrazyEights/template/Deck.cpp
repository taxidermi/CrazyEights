#include "Deck.h"

#include <algorithm>
#include <random>

#include "Card.h"

Deck::Deck(const bool fillDeck, const int fillDeckTimes)
{
	this->deck_vector = {};
	if (fillDeck)
		this->FillDeck(fillDeckTimes);
}

int Deck::GetSize() const
{
	return static_cast<int>(this->deck_vector.size());
}

bool Deck::IsEmpty() const
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
	// Delete every pointer first (no dangling pointers or memory leaks), then clear the deck
	// Reverse for loop because... todo: explain this
	for (int i = static_cast<int>(this->deck_vector.size()) - 1; i > 0; i--)
		delete this->deck_vector[i];
	this->deck_vector.clear();
}

void Deck::FillDeck(const int times)
{
	/*for (int x = 0; x < times; x++)
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
	}*/
	for (const std::string& suit : Card::CardSuits)
	{
		for (int i = 1; i < 14; i++)
			this->deck_vector.push_back(new Card(i, suit));
	}
}

void Deck::AddCard(Card* new_card)
{
	if (new_card == nullptr)
		return;
	this->deck_vector.push_back(new_card);
	for (const std::function<void(Card*)>& onCardAddedFunc : OnCardAddedSignals)
		onCardAddedFunc(new_card);
}

Card* Deck::PeekCard(const int index) const
{
	if (index < 0 || index > this->deck_vector.size() - 1)
		return nullptr;
	return this->deck_vector[index];
}

Card* Deck::PeekTopCard() const
{
	const int top_card_index = this->GetSize() - 1;
	return this->PeekCard(top_card_index);
}

Card* Deck::GetCard(const int index)
{
	if (index < 0 || index > this->deck_vector.size() - 1)
		return nullptr;
	//Temporary variable must be created to return object after deleting card from vector.
	Card* card = this->deck_vector[index];
	RemoveCard(index);
	return card;
}

void Deck::RemoveCard(const int index)
{
	if (index < 0 || index > this->deck_vector.size() - 1)
		return;
	Card* card = this->deck_vector[index];
	this->deck_vector.erase(this->deck_vector.begin() + index);
	for (const std::function<void(Card*)>& onCardRemovedFunc : OnCardRemovedSignals)
		onCardRemovedFunc(card);
}

Card* Deck::GetTopCard()
{
	const int top_card_index = this->GetSize() - 1;
	return this->GetCard(top_card_index);
}