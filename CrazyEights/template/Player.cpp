#include "Player.h"

#include "../src/Utils.h"
#include "../src/Round.h"
#include "Deck.h"

Player::Player()
{
	this->name = "Unamed Player";
	this->hand = {};
	this->score = 0;
}

Player::Player(std::string playerName)
{
	this->name = playerName;
	this->hand = {};
	this->score = 0;
}

std::string Player::GetName()
{
	return this->name;
}

void Player::SetName(std::string new_name)
{
	this->name = new_name;
}

int Player::GetHandSize()
{
	return this->hand.size();
}

std::vector<Card*> Player::GetHand()
{
	return this->hand;
}

void Player::ClearHand()
{
	this->hand.clear();
}

Card* Player::PeekCard(int index)
{
	return this->hand[index];
}

bool Player::IsEmpty()
{
	return this->hand.empty();
}

Card* Player::GetCard(int index)
{
	//Temporary variable must be created to return object after deleting card from vector.
	Card* card = this->hand[index];
	this->hand.erase(this->hand.begin() + index);
	return card;
}

void Player::AddCard(Card* new_card)
{
	this->hand.push_back(new_card);
}

void Player::RemoveCard(int index)
{
	this->hand.erase(this->hand.begin() + index);
}

bool Player::RemoveCard(Card* cardToRemove)
{
	for (int i = 0; i < hand.size(); i++)
	{
		Card* card = hand[i];
		if (card == cardToRemove)
		{
			RemoveCard(i);
			return true;
		}
	}
	return false;
}

int Player::SumHand()
{
	int total = 0;
	for (Card* c : this->hand)
		total += c->GetRank();
	return total;
}

void Player::OutputHand(bool includeCardIndex)
{
	//Iterate through each card in hand and output toString for each one
	/*for (Card* c : this->hand)
		std::cout << c->ToString() << std::endl;*/
	Utils::PrintCards(hand, includeCardIndex);
}

void Player::ChangeScoreBy(int toAdd)
{
	this->score += toAdd;
}

void Player::SetScore(int newScore)
{
	this->score = newScore;
}

int Player::GetScore()
{
	return this->score;
}

bool Player::CanPlayerMatchCard(Card* otherCard)
{
	for (Card* card : this->hand)
	{
		if (card->DoesCardMatch(otherCard))
			return true;
	}
	return false;
}

std::vector<Card*> Player::GetMatchableCards(Card* otherCard)
{
	std::vector<Card*> matchableCards = {};
	for (Card* card : hand)
	{
		if (card->DoesCardMatch(otherCard))
			matchableCards.push_back(card);
	}
	return matchableCards;
}

PlayerTurn Player::AskPlayerForTurn(Card* topCard)
{
	bool canPlayerMatchCard = CanPlayerMatchCard(topCard);
	std::string askMessage = "What would you like to do? Draw [1], Place [" + std::string(canPlayerMatchCard ? "2]" : "No matching cards]") + ": ";
	int playerTurnInput = Utils::AskUserForInput(askMessage, 1, canPlayerMatchCard ? 2 : 1);
	return static_cast<PlayerTurn>(playerTurnInput - 1); // We - 1 from it because the user input option starts at 1 (better for user)
}


PlayerTurnResult Player::HandlePlayerTurn(Round* round)
{
	PlayerTurnResult turnResult = PlayerTurnResult::PASS;

	PlayerTurn playerTurn = AskPlayerForTurn(round->GetDiscardPile()->PeekTopCard());
	switch (playerTurn)
	{
		case PlayerTurn::DRAW:
		{
			// Draw card(s) until
			Card* drawnCard = nullptr;
			while (drawnCard == nullptr || !drawnCard->DoesCardMatch(round->GetDiscardPile()->PeekTopCard()))
			{
				drawnCard = round->GetCardDeck()->GetTopCard();
				AddCard(drawnCard);
				std::cout << "Drew card: " << drawnCard->ToString() << "\n";
			}
			// Give player option to place or keep(?) card
			int playerOption = Utils::AskUserForInput("What would you like to do with the drawn card? "
									   "([0] Keep, [1] Place): ", 0, 1);
			if (playerOption == 0) // Keep drawn card
				std::cout << "Keeping card, "; // no \n, adds the "ending turn" line to it
			else if (playerOption == 1) // Place drawn card
			{
				// Take and place card onto discard pile. Will check if player wins
				if (!round->DiscardCard(this, drawnCard))
				{
					std::cout << "[ERROR] Failed to place drawn card!\n";
					break;
				}
			}
			break;
		}
		case PlayerTurn::PLACE:
		{
			std::vector<Card*> matchableCards = GetMatchableCards(round->GetDiscardPile()->PeekTopCard());
			std::cout << "Matchable cards: ";
			Utils::PrintCards(matchableCards, true);
			int cardToPlaceIndex = Utils::AskUserForInput("What card would you like to place?: ", 0, matchableCards.size() - 1);
			Card* cardToPlace = matchableCards[cardToPlaceIndex];
			// Take and place card onto discard pile. Will check if player wins
			if (!round->DiscardCard(this, cardToPlace))
			{
				std::cout << "[ERROR] Failed to place card from index " << cardToPlaceIndex << "!\n";
				break;
			}
			break;
		}
	default:
		break;
	}

	return turnResult;
}
