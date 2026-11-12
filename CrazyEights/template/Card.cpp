#include "Card.h"

#include "../src/Utils/Math.h"
#include "../src/Utils/Utils.h"

const std::string Card::CardSuits[4] = { "Clubs", "Diamonds", "Hearts", "Spades" };

Card::Card(const int init_rank, const std::string& init_suit)
{
	this->rank = init_rank;
	this->suit = init_suit;
}

int Card::GetRank() const
{
	return this->rank;
}

std::string Card::GetSuit()
{
	return this->suit;
}

void Card::SetRank(const int new_rank)
{
	this->rank = new_rank;
}

void Card::SetSuit(const std::string& new_suit)
{
	this->suit = new_suit;
}

std::string Card::ToString()
{
	switch (this->GetRank())
	{
		case 11:
			return "Jack of " + this->GetSuit();
		case 12:
			return "Queen of " + this->GetSuit();
		case 13:
			return "King of " + this->GetSuit();
		default:
			return std::to_string(this->rank) + " of " + this->GetSuit();
	}
}

bool Card::DoesCardMatch(Card* otherCard) const
{
	return otherCard->GetRank() == this->rank || otherCard->GetSuit() == this->suit ||
		this->GetRank() == 8; // The eights are crazy!!! (like a wildcard)
}

int Card::GetCardScore() const
{
	switch (this->rank)
	{
		case 8: // Eights are crazy!!!
			return 50;
		case 11:
		case 12:
		case 13: // Face cards return 10
			return 10;
		default: // Rest of the cards return the face value
			return this->rank;
	}
}

Card* Card::CreateRandomCard()
{
	const std::string suit = CardSuits[Utils::Math::RandRange(0, 3)];
	const int rank = Utils::Math::RandRange(1, 13);
	return new Card(rank, suit);
}

std::string Card::GetCardSuitFromOption(const int option)
{
	switch (option)
	{
		case 0:
			return "Clubs";
		case 1:
			return "Diamonds";
		case 2:
			return "Hearts";
		case 3:
			return "Spades";
		default:
			break;
	}
	return "";
}

void Card::PrintCards(const std::vector<Card*>& cards, const bool includeCardIndex, const int cardIndexOffset)
{
	for (int i = 0; i < cards.size(); ++i)
	{
		Card* card = cards.at(i);
		if (card == nullptr)
			continue;
		std::cout << (includeCardIndex ? std::string("[" + std::to_string(i + cardIndexOffset) + "] ") : "")
			<< card->ToString();
		if (i != cards.size() - 1)
			std::cout << ", ";
	}
	std::cout << "\n";
}