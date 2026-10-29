#pragma once
#include <iostream>
#include <string>

#include "../template/Card.h"

namespace Utils
{
	template <typename T>
	static T AskUserForInput(std::string askMessage)
	{
		T userInput{};
		std::cout << askMessage;
		while (!(std::cin >> userInput)) {
			std::cin.clear(); // Clear error flags
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // Ignore bad input
			std::cout << "Invalid input! " << askMessage;
		}
		return userInput;
	}

	static int AskUserForInput(std::string askMessage, int min, int max)
	{
		int userInput;
		std::cout << askMessage;
		while (!(std::cin >> userInput) || userInput < min || userInput > max) {
			std::cin.clear(); // Clear error flags
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore bad input
			std::cout << "Invalid input! " << askMessage;
		}
		return userInput;
	}

	static void PrintCards(const std::vector<Card*>& cards, bool includeCardIndex = false)
	{
		for (int i = 0; i < cards.size(); ++i)
		{
			Card* card = cards.at(i);
			if (card == nullptr)
				continue;
			std::cout << (includeCardIndex ? std::string("[" + std::to_string(i) + "] ") : "") << card->ToString();
			if (i != cards.size() - 1)
				std::cout << ", ";
		}
		std::cout << "\n";
	}
};