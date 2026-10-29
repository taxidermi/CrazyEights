#include "Card.h"

Card::Card(int init_rank, std::string init_suit)
{
	this->rank = init_rank;
	this->suit = init_suit;
}

int Card::GetRank()
{
	return this->rank;
}

std::string Card::GetSuit()
{
	return this->suit;
}

void Card::SetRank(int new_rank)
{
	this->rank = new_rank;
}

void Card::SetSuit(std::string new_suit)
{
	this->suit = new_suit;
}

std::string Card::ToString()
{
	return std::to_string(this->rank) + " of " + this->GetSuit();
}

bool Card::DoesCardMatch(Card* otherCard)
{
	return otherCard->GetRank() == rank || otherCard->GetSuit() == suit ||
		this->GetRank() == 8; // The eights are crazy!!! (like a wildcard)
}