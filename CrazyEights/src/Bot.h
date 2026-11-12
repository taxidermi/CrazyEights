#pragma once

#include "../template/Player.h"

class Bot : public Player
{
public:
	Bot(const std::string& botName) : Player(botName) {}

	PlayerTurn AskPlayerForTurn(Card* topCard) override;
	PlayerTurnResult HandlePlayerTurn(Round* round) override;

private:
	PlayerPlaceCardResult HandlePlacingCard(Round* round, Card* card) override;
};