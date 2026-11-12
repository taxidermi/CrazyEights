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
	UpdateRoundState(RoundState::WAITING);
}

Round::~Round()
{
	if (GetCurrentRoundState() != RoundState::WAITING)
		Cleanup();
}

void Round::Cleanup()
{
	// Delete and clear the piles of decks
	cardDeck->Clear();
	discardPile->Clear();
	// Don't delete the players as they are also stored and reused in the 'Game' class.
	for (Player* player : players)
		player->Cleanup();
	players.clear();
	UpdateRoundState(RoundState::WAITING);
}

Deck* Round::GetCardDeck() const {
	return cardDeck;
}

Deck* Round::GetDiscardPile() const {
	return discardPile;
}

RoundState Round::GetCurrentRoundState() const {
	return currentRoundState;
}

void Round::SetCurrentRoundState(const RoundState newState)
{
	currentRoundState = newState;
}

RoundState Round::GetPreviousRoundState() const {
	return previousRoundState;
}

void Round::SetPreviousRoundState(const RoundState newState)
{
	previousRoundState = newState;
}

void Round::UpdateRoundState(const RoundState newState)
{
	SetPreviousRoundState(currentRoundState);
	SetCurrentRoundState(newState);
}

void Round::StartRound()
{
	Utils::PrintTitle("STARTING ROUND", '=');
	UpdateRoundState(RoundState::STARTING);
	Utils::SleepForMs(750);
	// Setup card deck
	if (!cardDeck->IsEmpty())
		cardDeck->Clear();
	const int cardDeckSize = Utils::AskUserForInput("Please enter the number of card decks you want to play with (1-10): ",
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
	Utils::SleepForMs(500);
	UpdateRoundState(RoundState::PLAYING);
	Utils::PrintTitle("ROUND START", '=');
	Utils::SleepForMs(500);
	while (currentRoundState == RoundState::PLAYING)
	{
		// Loop through all players to let them perform their turn
		for (Player* player : players)
		{
			// Check if the current round is finished before giving turn
			if (currentRoundState == RoundState::FINISHED)
				break;
			// Output name, turn and their hand
			Utils::PrintTitle(player->GetName() + "'s turn", '-');
			Utils::SleepForMs(750);
			std::cout << "Your hand: ";
			player->OutputHand();
			Utils::SleepForMs(500);
			// Print the top card so the player knows what card they need to match
			std::cout << "Top card: " << GetDiscardPile()->PeekTopCard()->ToString() << "\n";
			Utils::SleepForMs(500);
			// Handle and perform player's turn. Asks the player what they want to do: place or draw.
			// If the player is a bot then it will do it's own logic
			PlayerTurnResult turnResult = player->HandlePlayerTurn(this);
			if (turnResult != PlayerTurnResult::WIN) // If player hasn't won, end their turn
				std::cout << "End of " << player->GetName() << "'s turn\n";
			Utils::SleepForMs(500);
		}
	}
	// Round over, delete this round object, which will call "Cleanup()", and go back to Game::Start()
	delete this;
}

void Round::OnRoundFinished(Player* winningPlayer) const {
	std::cout << winningPlayer->GetName() << " Wins! ";
	Utils::SleepForMs(500);
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
	Utils::SleepForMs(250);
	std::cout << "Ending round...\n";
	Utils::SleepForMs(1000);
}

bool Round::DiscardCard(Player* player, Card* card) const {
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

void Round::RefillDeck() const {
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
	discardPile->Clear();
	// Now that the discard pile is empty, add the current top card back
	discardPile->AddCard(currentTopCard);
}
