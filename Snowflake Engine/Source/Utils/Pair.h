#pragma once

namespace Snowflake
{
    template<typename L, typename R>
    class Pair
    {
    public:
        Pair(L Left, R Right)
            : m_Left(Left), m_Right(Right) {}

        L GetLeft() { return m_Left; }
        L GetLeft() const { return m_Left; }

        R GetRight() { return m_Right; }
        R GetRight() const { return m_Right; }
    private:
        L m_Left;
        R m_Right;
    };

    template<typename L, typename R>
    inline std::ostream& operator<<(std::ostream& OStream, const Pair<L, R> InPair)
    {
        return OStream << "Pair (Left: " << InPair.GetLeft() << ", Right: " << InPair.GetRight() << ")";
    }
}