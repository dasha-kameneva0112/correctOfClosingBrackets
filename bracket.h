#ifndef BRACKET_H
#define BRACKET_H
#include <QStringList>
#include <functional>

class bracket
{
public:
    bracket();
    bracket (const QStringList& code, int indexOfLineWithBracket, int position);

    enum BracketType{
        Round,
        Square,
        Curly
    };
    enum BracketSide{
        Opening,
        Closing
    };

    BracketType type;
    BracketSide side;
    int numberOfLine; //номер строки кода с данной скобкой
    int positionOfBraket; //позиция скобки в строке
    bool correctOfOrder; //правильность порядка скобки

    bool operator==(const bracket& other) const
    {
        return (type == other.type && side == other.side &&
                numberOfLine == other.numberOfLine &&
                positionOfBraket == other.positionOfBraket && correctOfOrder == other.correctOfOrder);
    }
};

inline size_t qHash(const bracket& key, size_t seed = 0) noexcept
{
    // Комбинируем хеши всех полей, которые участвуют в operator==
    return qHashMulti(seed,
                      static_cast<int>(key.type),
                      static_cast<int>(key.side),
                      key.numberOfLine,
                      key.positionOfBraket,
                      key.correctOfOrder);
}


#endif // BRACKET_H
