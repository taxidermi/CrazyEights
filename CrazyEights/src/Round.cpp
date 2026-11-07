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
	cardDeck = new Deck(); // Don't fill deck with cards. It gets filled in StartRound()
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
	Utils::PrintTitle("STARTING ROUND", '=');
	UpdateRoundState(RoundState::STARTING);
	// Setup card deck
	if (!cardDeck->IsEmpty())
		cardDeck->Clear();
	int cardDeckSize = Utils::AskUserForInput("Please enter the number of card decks you want to play with (1-10): ",
		1, 10);
	cardDeck->FillDeck(cardDeckSize);
	std::cout << "Created card deck with " << cardDeck->GetSize() << " cards!\n";
	cardDeck->Shuffle();
	// Setup players
	// Shuffle players array to randomise the order
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(this->players.begin(), this->players.end(), g);
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
	Utils::PrintTitle("ROUND START", '=');
	while (currentRoundState == RoundState::PLAYING)
	{
		// Loop through all players to let them perform their turn
		for (Player* player : players)
		{
			// Check if the current round is finished before giving turn
			if (currentRoundState == RoundState::FINISHED)
				break;
			Utils::PrintTitle(player->GetName() + "'s turn", '-');
			std::cout << "Your hand: ";
			player->OutputHand();
			// Print top card
			std::cout << "Top card: " << GetDiscardPile()->PeekTopCard()->ToString() << "\n";
			// Handle player's turn
			PlayerTurnResult turnResult = player->HandlePlayerTurn(this);
			if (turnResult != PlayerTurnResult::WIN) // If player hasn't won, end their turn
				std::cout << "End of " << player->GetName() << "'s turn\n";
		}
	}
	// Round over, back to Game::Start()
}

void Round::OnRoundFinished(Player* winningPlayer)
{
	std::cout << winningPlayer->GetName() << " Wins! ";
	// Total up the score for the winning player
	int totalScore = 0;
	for (Player* player : players)
	{
		if (player == winningPlayer)
			continue;
		for (Card* card : player->GetHand())
			totalScore += card->GetCardScore();
	}
	winningPlayer->SetScore(totalScore);
	std::cout << "Winning score: " << std::to_string(totalScore) << "\n";
	std::cout << "Ending round...\n";
}

bool Round::DiscardCard(Player* player, Card* card)
{
	// Remove card from player's hand (via reference)
	if (card == nullptr || !player->RemoveCard(card))
	{
		std::cout << "[ERROR] Failed to place card!\n";
		return false;
	}
	// Place card on to the top of the discard pile
	discardPile->AddCard(card);
	std::cout << "Placed card: " << card->ToString() << "\n";
	return true;
}

void Round::RefillDeck()
{
	// Store the current top card from the discard pile
	Card* currentTopCard = discardPile->GetTopCard();
	// Get the top card each time and add it to the card deck
	for (int i = 0; i < discardPile->GetSize(); i++)
	{
		Card* card = discardPile->GetTopCard();
		if (card == nullptr)
			continue;
		cardDeck->AddCard(card);
	}
}