#pragma once

#include "../template/Player.h"

class Bot : public Player
{
public:
	Bot(std::string botName) : Player(botName) {}
};