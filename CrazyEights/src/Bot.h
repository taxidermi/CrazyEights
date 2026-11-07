#pragma once

#include "../template/Player.h"

class Bot : public Player
{
public:
	Bot(std::string botName) : Player(botName) {}

	PlayerTurn AskPlayerForTurn(Card* topCard) override;
	PlayerTurnResult HandlePlayerTurn(Round* round) override;
	bool HandlePlacingCard(Round* round, Card* card) override;
};