#pragma once

namespace Snowflake
{
    class Vector2
    {
    public:
        Vector2(float X, float Y)
            : m_X(X), m_Y(Y) {}

        std::string ToString() const
        {
            std::stringstream StringStream;
            StringStream << "Vector2(X: " << m_X << ", Y: " << m_Y << ")";
            
            return StringStream.str(); 
        }

        float X() { return m_X; }
        float X() const { return m_X; }

        float Y() { return m_Y; }
        float Y() const { return m_Y; }
        
    private:
        float m_X, m_Y;
    };

    inline Vector2 operator+(Vector2 LeftVec2, Vector2 RightVec2)
    {
        Vector2 Result = Vector2(LeftVec2.X() + RightVec2.X(), LeftVec2.Y() + RightVec2.Y());
        return Result;
    }

    inline Vector2 operator-(Vector2 LeftVec2, Vector2 RightVec2)
    {
        Vector2 Result = Vector2(LeftVec2.X() - RightVec2.X(), LeftVec2.Y() - RightVec2.Y());
        return Result;
    }

    inline Vector2 operator*(Vector2 LeftVec2, Vector2 RightVec2)
    {
        Vector2 Result = Vector2(LeftVec2.X() * RightVec2.X(), LeftVec2.Y() * RightVec2.Y());
        return Result;
    }
}