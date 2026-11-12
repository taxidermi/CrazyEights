#pragma once
#include <iostream>

namespace Utils::Math
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
}