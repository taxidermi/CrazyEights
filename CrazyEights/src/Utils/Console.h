#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Utils.h"
#include "../Structs/Color.h"

namespace Utils::Console
{
	/**
	* Clear the console/terminal/screen.
	* ToDo: Test multi-platform (windows + linux) support
	*/
	static void Clear()
	{
#ifdef _WIN32
		system("cls");
#endif
#ifdef __unix__
		system("clear");
#endif
	}

	/**
	 * Print out a coloured line to the console.
	 * @param output What to output to the console.
	 * @param color The color to use.
	 */
	static void PrintColoredLine(const std::string& output, const Color color)
	{
		std::cout << color.GetConsoleColorOutput() << output << "\033[0m\t\t\n";
	}

	/**
	 * Print out a colored character to the console. Will not create a new line.
	 * @param output What character to output to the console.
	 * @param color The color to use.
	 * @param endSpace Should a space be added to the end?
	 */
	static void PrintColoredText(const char output, const Color color, const bool endSpace = true)
	{
		std::cout << color.GetConsoleColorOutput() << output << "\033[0m";
		if (endSpace)
			std::cout << ' ';
	}

	/**
	 * Print out a colored message to the console. Will not create a new line.
	 * @param output What to output to the console.
	 * @param color The color to use.
	 * @param endSpace Should a space be added to the end?
	 */
	static void PrintColoredText(const std::string& output, const Color color, const bool endSpace = true)
	{
		std::cout << color.GetConsoleColorOutput() << output << "\033[0m";
		if (endSpace)
			std::cout << ' ';
	}

	static const std::vector<Color> ColorfulLineColors = {
		Colors::Red, Colors::Orange, Colors::Yellow, Colors::Lime, Colors::Green, Colors::Aqua, Colors::LightBlue,
		Colors::Blue, Colors::DeepBlue, Colors::Purple, Colors::HotPink, Colors::Pink
	};

	/**
	 * Print out a colourful line to the console. Will start a new line once finished.
	 * @param output The text to output.
	 */
	static void PrintColorfulLine(const std::string& output)
	{
		int currentRainbowIndex = 0;
		for (const char character : output)
		{
			if (character == ' ') // Don't output a colored character if it is a space
				std::cout << character;
			else
			{
				PrintColoredText(character, ColorfulLineColors[currentRainbowIndex], false);
				if (currentRainbowIndex == ColorfulLineColors.size() - 1)
					currentRainbowIndex = 0;
				else
					currentRainbowIndex++;
			}
		}
		std::cout << "\n";
	}

	/**
	 * Print a message to the console character by character by sleeping between each character.
	 * @param output The text to output. Note that any "\n" will not work.
	 * @param delayBetweenCharacters The milliseconds between each output.
	 * @param newLine Should a new line be started.
	 */
	static void PrintAnimated(const std::string& output, const int delayBetweenCharacters = 20, const bool newLine = true)
	{
		for (const char i : output)
		{
			std::cout << i;
			SleepForMs(delayBetweenCharacters);
		}
		if (newLine)
			std::cout << "\n";
	}

	/**
	 * Print a colored message to the console character by character by sleeping between each character.
	 * @param output The text to output. Note that any "\n" will not work.
	 * @param color The text color
	 * @param delayBetweenCharacters The milliseconds between each output.
	 * @param newLine Should a new line be started once the output is finished.
	 */
	static void PrintAnimated(const std::string& output, Color color, const int delayBetweenCharacters = 20,
		const bool newLine = true)
	{
		for (const char i : output)
		{
			PrintColoredText(i, color, false);
			SleepForMs(delayBetweenCharacters);
		}
		if (newLine)
			std::cout << "\n";
	}

	/**
	 * Print a colorful message to the console character by character by sleeping between each character.
	 * @param output The text to output. Note that any "\n" will not work.
	 * @param delayBetweenCharacters The milliseconds between each output.
	 * @param newLine Should a new line be started once the output is finished.
	 */
	static void PrintColorfulAnimated(const std::string& output, const int delayBetweenCharacters = 20,
		const bool newLine = true)
	{
		int currentRainbowIndex = 0;
		for (const char character : output)
		{
			if (character == ' ') // Don't output a colored character if it is a space
				std::cout << character;
			else
			{
				PrintColoredText(character, ColorfulLineColors[currentRainbowIndex], false);
				if (currentRainbowIndex == ColorfulLineColors.size() - 1)
					currentRainbowIndex = 0;
				else
					currentRainbowIndex++;
			}
			SleepForMs(delayBetweenCharacters);
		}
		if (newLine)
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
	 * Print a colored splitter line using the splitter param and making it as long as the splitterLength param.
	 * @param splitter The splitter character
	 * @param color The color of the splitter
	 * @param splitterLength How many '-' to print
	 */
	static void PrintSplitter(const char splitter = '=', const Color color = Colors::White,
		const int splitterLength = 80)
	{
		std::string splitterOutput;
		for (int i = 0; i < splitterLength; ++i)
			splitterOutput += splitter;
		PrintColoredLine(splitterOutput, color);
	}

	/**
	 * Print a title line, with a splitter above and below.
	 * @param title The title to print, centered with the splitters
	 * @param splitter The splitter character
	 * @param splitterLength The length of the splitter
	 */
	static void PrintTitle(const std::string& title, const char splitter = '=', const int splitterLength = 80)
	{
		PrintSplitter(splitter, splitterLength);
		const int centerSpaces = (splitterLength - static_cast<int>(title.size())) / 2;
		std::cout << std::string(centerSpaces, ' ');
		std::cout << title << "\n";
		PrintSplitter(splitter, splitterLength);
	}

	/**
	 * Print a colored title line, with a splitter above and below.
	 * @param title The title to print, centered with the splitters
	 * @param splitterColor The color of the splitter
	 * @param titleColor The color of the title
	 * @param splitter The splitter character
	 * @param splitterLength The length of the splitter
	 */
	static void PrintTitle(const std::string& title, const Color splitterColor, const Color titleColor,
		const char splitter = '=', const int splitterLength = 80)
	{
		PrintSplitter(splitter, splitterColor, splitterLength);
		const int centerSpaces = (splitterLength - static_cast<int>(title.size())) / 2;
		std::cout << std::string(centerSpaces, ' ');
		PrintColoredLine(title, titleColor);
		PrintSplitter(splitter, splitterColor, splitterLength);
	}

	/**
	 * Print a colorful title line, with a splitter above and below.
	 * @param title The title to print, centered with the splitters
	 * @param splitter The splitter character
	 * @param splitterColor The splitter color
	 * @param splitterLength The length of the splitter
	 */
	static void PrintColorfulTitle(const std::string& title, const Color splitterColor, const char splitter = '=',
		const int splitterLength = 80)
	{
		PrintSplitter(splitter, splitterColor, splitterLength);
		const int centerSpaces = (splitterLength - static_cast<int>(title.size())) / 2;
		std::cout << std::string(centerSpaces, ' ');
		PrintColorfulLine(title);
		PrintSplitter(splitter, splitterColor, splitterLength);
	}
}