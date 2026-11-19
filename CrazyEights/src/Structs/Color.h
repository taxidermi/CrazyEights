#pragma once
#include <string>

struct Color
{
private:
    float R = 1.0f;
    float G = 1.0f;
    float B = 1.0f;
    float A = 1.0f;

public:
    Color(const float r, const float g, const float b, const float a = 1.0f)
    {
        R = r;
        G = g;
        B = b;
        A = a;
    }

    float GetR() const
    {
        return R;
    }
    void SetR(const float r)
    {
        R = r;
    }

    float GetG() const
    {
        return G;
    }
    void SetG(const float g)
    {
        G = g;
    }

    float GetB() const
    {
        return B;
    }
    void SetB(const float b)
    {
        B = b;
    }

    float GetA() const
    {
        return A;
    }
    void SetA(const float a)
    {
        A = a;
    }

    static Color From255Byte(const int r, const int g, const int b, const int a)
    {
        return {static_cast<float>(r / 255), static_cast<float>(g / 255), static_cast<float>(b / 255), static_cast<float>(a / 255)};
    }

    /**
     * Get the correct console output string to change the console text (foreground) color to this.
     * @return The formatted string output for std::cout
     */
    std::string GetConsoleColorOutput() const
    {
        const int r = R * 255.0f;
        const int g = G * 255.0f;
        const int b = B * 255.0f;
        return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    }
};

namespace Colors
{
    static const Color White = Color(1.0f, 1.0f, 1.0f);
    static const Color Black = Color(0.0f, 0.0f, 0.0f);
    static const Color Red = Color(1.0f, 0.0f, 0.0f);
    static const Color LightRed = Color(1.0f, 0.33f, 0.0f);
    static const Color Orange = Color(1.0f, 0.67f, 0.0f);
    static const Color Yellow = Color(1.0f, 1.0f, 0.0f);
    static const Color Lime = Color(0.67f, 1.0f, 0.0f);
    static const Color Green = Color(0.0f, 1.0f, 0.0f);
    static const Color Aqua = Color (0.0f, 1.0f, 0.67f);
    static const Color LightBlue = Color(0.0f, 1.0f, 1.0f);
    static const Color Blue = Color(0.0f, 0.5f, 1.0f);
    static const Color DeepBlue = Color(0.0f, 0.0f, 1.0f);
    static const Color Purple = Color(0.67f, 0.0f, 1.0f);
    static const Color HotPink = Color(1.0f, 0.0f, 1.0f);

    static const Color Pink = Color(1.0f, 0.6f, 0.95f);

    static const std::vector<Color> PlayerColors =
    {
        LightRed, Orange, Yellow, Lime, Green, Aqua, LightBlue, DeepBlue, Purple, HotPink, Pink
    };
}