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
	for (int i = GetHandSize() - 1; i >= 0; --i)
		RemoveCard(i);
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
	RemoveCard(index);
	return card;
}

void Player::AddCard(Card* new_card)
{
	this->hand.push_back(new_card);
	for (const std::function<void(Card*)>& onCardAddedFunc : OnCardAddedSignals)
		onCardAddedFunc(new_card);
	OnCardAdded(new_card);
}

void Player::RemoveCard(int index)
{
	Card* card = this->hand[index];
	this->hand.erase(this->hand.begin() + index);
	for (const std::function<void(Card*)>& onCardRemovedFunc : OnCardRemovedSignals)
		onCardRemovedFunc(card);
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
			// Draw card(s) until a matching card is drawn
			Card* drawnCard = nullptr;
			while (drawnCard == nullptr || !drawnCard->DoesCardMatch(round->GetDiscardPile()->PeekTopCard()))
			{
				// If the draw deck is empty, refill it using the discard pile
				if (round->GetCardDeck()->IsEmpty())
					round->RefillDeck();
				drawnCard = round->GetCardDeck()->GetTopCard();
				if (drawnCard == nullptr)
					continue;
				AddCard(drawnCard);
				std::cout << "Drew card: " << drawnCard->ToString() << "\n";
			}
			// Give player option to place or keep(?) card
			int playerOption = Utils::AskUserForInput("What would you like to do with the drawn card? "
									   "([1] Keep, [2] Place): ", 1, 2);
			if (playerOption == 1) // Keep drawn card
				std::cout << "Keeping card, "; // no \n, adds the "ending turn" line to it
			else if (playerOption == 2) // Place drawn card
				// Take and place card onto discard pile. Will check if player wins and handle the type of card
				HandlePlacingCard(round, drawnCard);
			break;
		}
		case PlayerTurn::PLACE:
		{
			std::vector<Card*> matchableCards = GetMatchableCards(round->GetDiscardPile()->PeekTopCard());
			std::cout << "Matchable cards: ";
			// Print and ask user to pick a card to remove. The index is offset by 1, so they don't have to enter 0
			// which is across the keyboard
			Utils::PrintCards(matchableCards, true, 1);
			int cardToPlaceIndex = Utils::AskUserForInput("What card would you like to place?: ", 1,
				matchableCards.size());
			Card* cardToPlace = matchableCards[cardToPlaceIndex - 1];
			// Take and place card onto discard pile. Will check if player wins and handle the type of card
			HandlePlacingCard(round, cardToPlace);
			break;
		}
	default:
		break;
	}

	return turnResult;
}

bool Player::HandlePlacingCard(Round* round, Card* card)
{
	// Take and place card onto discard pile
	if (!round->DiscardCard(this, card))
	{
		std::cout << "[ERROR] Failed to place card: " << card->ToString() << "!\n";
		return false;
	}
	// Check if player's hand is empty (they win!)
	if (GetHandSize() == 0)
	{
		round->UpdateRoundState(RoundState::FINISHED); // Exit game while loop
		round->OnRoundFinished(this); // This player won!
	}
	// Check if the card placed was an 8. If so, give the player the option to pick a suit
	else if (card->GetRank() == 8)
	{
		// Offset option/index by 1 so user doesn't have to press 0
		int newSuitOption = Utils::AskUserForInput("An eight was played! Pick the next suit ([1] Clubs, "
											 "[2] Diamonds, [3] Hearts, [4] Spades): ", 1, 4);
		card->SetSuit(Utils::GetCardSuitFromOption(newSuitOption - 1));
		std::cout << "Suit picked: " << card->GetSuit() << "\n";
	}
	return true;
}

void Player::OnCardAdded(Card* card)
{
}

void Player::OnCardRemoved(Card* card)
{
}
