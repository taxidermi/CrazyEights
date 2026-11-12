#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace Utils::Console
{
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
		const int centerSpaces = (splitterLength - static_cast<int>(title.size())) / 2;
		std::cout << std::string(centerSpaces, ' ');
		std::cout << title << "\n";
		PrintSplitter(splitter, splitterLength);
	}

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
	 * Print a message to the console character by character by sleeping between each character.
	 * @param output The text to output. Note that any "\n" will not work.
	 * @param delayBetweenCharacters The milliseconds between each output.
	 */
	static void PrintAnimated(const std::string& output, const int delayBetweenCharacters = 20)
	{
		for (const char i : output)
		{
			std::cout << i;
			SleepForMs(delayBetweenCharacters);
		}
		std::cout << "\n";
	}
}