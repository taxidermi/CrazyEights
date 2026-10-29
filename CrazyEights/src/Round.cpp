#include "Round.h"

#include <utility>

#include "../src/Utils.h"
#include "../template/Deck.h"
#include "../template/Player.h"

Round::Round(std::vector<Player*> plrs)
{
	players = std::move(plrs);
	cardDeck = new Deck(true); // Fill deck with cards
	discardPile = new Deck(); // Leave discard deck empty
}

Deck* Round::GetCardDeck()
{
	return cardDeck;
}

Deck* Round::GetDiscardPile()
{
	return discardPile;
}

RoundState Round::GetCurrentRoundState()
{
	return currentRoundState;
}

void Round::SetCurrentRoundState(RoundState newState)
{
	currentRoundState = newState;
}

RoundState Round::GetPreviousRoundState()
{
	return previousRoundState;
}

void Round::SetPreviousRoundState(RoundState newState)
{
	previousRoundState = newState;
}

void Round::UpdateRoundState(RoundState newState)
{
	SetPreviousRoundState(currentRoundState);
	SetCurrentRoundState(newState);
}

void Round::StartRound()
{
	UpdateRoundState(RoundState::STARTING);
	// Setup decks
	if (cardDeck->IsEmpty())
		cardDeck->FillDeck();
	cardDeck->Shuffle(); // Gets shuffled anyway when being created, but doesn't hurt!
	// Add 5 cards to each player's hand
	for (Player* player : players)
	{
		for (int i = 0; i < 5; i++)
			player->AddCard(cardDeck->GetTopCard());
	}

	// Take the top card from the deck and place it in the discard pile
	discardPile->AddCard(cardDeck->GetTopCard());
	// Start game
	UpdateRoundState(RoundState::PLAYING);
	while (currentRoundState == RoundState::PLAYING)
	{
		// Loop through all players to let them perform their turn
		for (Player* player : players)
		{
			// Check if the current round is finished before giving turn
			if (currentRoundState == RoundState::FINISHED)
				break;
			std::cout << "--------------------\n" << player->GetName() << "'s turn\n";
			std::cout << "Your hand: ";
			player->OutputHand();
			// Print top card
			std::cout << "Top card: " << discardPile->PeekTopCard()->ToString() << "\n";
			PlayerTurn playerTurn = player->AskPlayerForTurn(discardPile->PeekTopCard());
			switch (playerTurn)
			{
				case PlayerTurn::DRAW:
				{
					// Draw card(s) until
					Card* drawnCard = nullptr;
					while (drawnCard == nullptr || !drawnCard->DoesCardMatch(discardPile->PeekTopCard()))
					{
						drawnCard = cardDeck->GetTopCard();
						player->AddCard(drawnCard);
						std::cout << "Drew card: " << drawnCard->ToString() << "\n";
					}
					// Give player option to place or keep(?) card
					int playerOption = Utils::AskUserForInput("What would you like to do with the drawn card? "
											   "[0] Keep, [1] Place): ", 0, 1);
					if (playerOption == 0) // Keep drawn card
						std::cout << "Keeping card, "; // no \n, adds the "ending turn" line to it
					else if (playerOption == 1) // Place drawn card
					{
						// Take and place card onto discard pile. Will check if player wins
						if (!DiscardCard(player, drawnCard))
						{
							std::cout << "[ERROR] Failed to place drawn card!\n";
							break;
						}
					}
					break;
				}
				case PlayerTurn::PLACE:
				{
					std::vector<Card*> matchableCards = player->GetMatchableCards(discardPile->PeekTopCard());
					std::cout << "Matchable cards: ";
					Utils::PrintCards(matchableCards, true);
					int cardToPlaceIndex = Utils::AskUserForInput("What card would you like to place?: ", 0, matchableCards.size() - 1);
					Card* cardToPlace = matchableCards[cardToPlaceIndex];
					// Take and place card onto discard pile. Will check if player wins
					if (!DiscardCard(player, cardToPlace))
					{
						std::cout << "[ERROR] Failed to place card from index " << cardToPlaceIndex << "!\n";
						break;
					}
					break;
				}
				default:
					break;
			}
			std::cout << "Ending " << player->GetName() << "'s turn...\n";
		}
	}
	// Round over, back to Game::Start()
}

bool Round::DiscardCard(Player* player, Card* card)
{
	/// Remove card from player's hand (via reference)
	if (card == nullptr || !player->RemoveCard(card))
	{
		std::cout << "[ERROR] Failed to place card!\n";
		return false;
	}
	// Place card on to the top of the discard pile
	discardPile->AddCard(card);
	std::cout << "Placed card: " << card->ToString() << "\n";
	// Check if player's hand is empty
	if (player->GetHandSize() == 0)
	{
		std::cout << player->GetName() << " Wins! Ending round...\n";
		UpdateRoundState(RoundState::FINISHED); // exits while loop
	}
	return true;
}
