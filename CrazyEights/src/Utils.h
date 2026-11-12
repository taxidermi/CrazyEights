#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

#include "../template/Card.h"

namespace Utils
{
	/**
	 * Generate a random number between the min and the max param
	 * @param min The min number
	 * @param max The max number
	 * @return Random int between min and max
	 */
	static int RandRange(const int min, const int max)
	{
		return rand() % (max - min + 1) + min;
	}

	/**
	 * Ask the user for input. Outputs a message before allowing input.
	 * @tparam T The type of value to return.
	 * @param askMessage What message to output before allowing input.
	 * @return The value that the user inputted, of type T
	 */
	template <typename T>
	static T AskUserForInput(const std::string& askMessage)
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

	/**
	 * Ask the user to input a number. Outputs a message before allowing input. Only allows numbers between the
	 * min and max parameter.
	 * @param askMessage What message to output before allowing input.
	 * @param min The minimum number allowed to enter.
	 * @param max The maximum number allowed to enter.
	 * @return The number that the user inputted
	 */
	static int AskUserForInput(const std::string &askMessage, const int min, const int max)
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

	/**
	 * Print the given vector of cards in one line and in a clean format.
	 * @param cards The cards to output
	 * @param includeCardIndex Should the index of the card be printed (in [] brackets)
	 * @param cardIndexOffset Offset the card index, for making user input nicer
	 */
	static void PrintCards(const std::vector<Card*>& cards, const bool includeCardIndex = false, const int cardIndexOffset = 0)
	{
		for (int i = 0; i < cards.size(); ++i)
		{
			Card* card = cards.at(i);
			if (card == nullptr)
				continue;
			std::cout << (includeCardIndex ? std::string("[" + std::to_string(i + cardIndexOffset) + "] ") : "")
				<< card->ToString();
			if (i != cards.size() - 1)
				std::cout << ", ";
		}
		std::cout << "\n";
	}

	/**
	 * Print a splitter line using the splitter param and making it as long as the splitterLength param.
	 * @param splitter The splitter character
	 * @param splitterLength How many '-' to print
	 */
	static void PrintSplitter(const char splitter = '=', const int splitterLength = 80)
	{
		std::string splitterOutput;
		for (int i = 0; i < splitterLength; ++i)
			splitterOutput += splitter;
		std::cout << splitterOutput << "\n";
	}

	/**
	 * Print a title line, with a splitter above and below.
	 * @param title The title to print, centered with the splitters
	 * @param splitter The splitter character
	 * @param splitterLength The length of the splitter
	 */
	static void PrintTitle(const std::string &title, const char splitter = '=', const int splitterLength = 80)
	{
		PrintSplitter(splitter, splitterLength);
		int centerSpaces = (splitterLength - static_cast<int>(title.size())) / 2;
		std::cout << std::string(centerSpaces, ' ');
		std::cout << title << "\n";
		PrintSplitter(splitter, splitterLength);
	}

	/**
	 * Get the suit from a user input option.
	 * @param option The suit option
	 * @return The suit string
	 */
	static std::string GetCardSuitFromOption(const int option)
	{
		switch (option)
		{
		case 0:
			return "Clubs";
		case 1:
			return "Diamonds";
		case 2:
			return "Hearts";
		case 3:
			return "Spades";
		default:
			break;
		}
		return "";
	}

	/**
	* Clear the console/terminal/screen.
	* ToDo: Add multi-platform (windows + linux) support
	*/
	static void ClearConsole()
	{
		system("cls");
	}

	/**
	* Sleep this thread for the given milliseconds.
	* \param ms How long to sleep for, in milliseconds.
	*/
	static void SleepForMs(const int ms)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}

	/**
	* Sleep this thread for the given seconds.
	* \param s How long to sleep for, in seconds.
	*/
	static void SleepForS(const int s)
	{
		std::this_thread::sleep_for(std::chrono::seconds(s));
	}
};