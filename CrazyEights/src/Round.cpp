#include "Round.h"

#include <utility>
#include <algorithm>
#include <random>

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
	// Setup players
	// Shuffle players array to randomise the order
	std::random_device rd;
	std::mt19937 g(rd());
	std::ranges::shuffle(players, g);
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
			std::cout << "Top card: " << GetDiscardPile()->PeekTopCard()->ToString() << "\n";
			// Handle player's turn
			PlayerTurnResult turnResult = player->HandlePlayerTurn(this);
			if (turnResult == PlayerTurnResult::PASS) // TurnResult == WIN
			{
				std::cout << "Ending " << player->GetName() << "'s turn...\n";
				break;
			}
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
		UpdateRoundState(RoundState::FINISHED); // Exits while loop
	}
	return true;
}
