#pragma once

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

    static Color From255Bit(const int r, const int g, const int b, const int a)
    {
        return {static_cast<float>(r / 255), static_cast<float>(g / 255), static_cast<float>(b / 255), static_cast<float>(a / 255)};
    }
};

namespace Colors
{
    static const Color White = Color();
    static const Color Red = Color(1.0f, 0.0f, 0.0f);
}