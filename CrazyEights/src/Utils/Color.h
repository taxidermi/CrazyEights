#pragma once
#include <iostream>
#include <map>

namespace Utils::Color
{
    enum class ConsoleColor
    {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        BRIGHTBLACK,
        BRIGHTRED,
        BRIGHTGREEN,
        BRIGHTYELLOW,
        BRIGHTBLUE,
        BRIGHTMAGENTA,
        BRIGHTCYAN,
        BRIGHTWHITE
    };

    static const std::map<ConsoleColor, std::string> ConsoleColorTextCodes =
    {
        {ConsoleColor::BLACK, "32"},{ConsoleColor::RED, "31"},{ConsoleColor::GREEN, "32"},
        {ConsoleColor::YELLOW, "33"},{ConsoleColor::BLUE, "34"},{ConsoleColor::MAGENTA, "35"},
        {ConsoleColor::CYAN, "36"},{ConsoleColor::WHITE, "37"},
        {ConsoleColor::BRIGHTBLACK, "90"},{ConsoleColor::BRIGHTRED, "91"},{ConsoleColor::BRIGHTGREEN, "92"},
        {ConsoleColor::BRIGHTYELLOW, "93"},{ConsoleColor::BRIGHTBLUE, "94"},{ConsoleColor::BRIGHTMAGENTA, "95"},
        {ConsoleColor::BRIGHTCYAN, "96"},{ConsoleColor::BRIGHTWHITE, "97"},
    };

    static std::string GetConsoleColorCode(const ConsoleColor color)
    {
        return ConsoleColorTextCodes.at(color);
    }
}
