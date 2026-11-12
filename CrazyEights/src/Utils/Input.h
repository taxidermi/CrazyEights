#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

namespace Utils::Input
{
    /**
     * Wait for the user to enter any input.
     */
    static void WaitForUserInput()
    {
        std::cin.ignore();
        std::cin.clear();
        std::cin.get();
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
}