#ifndef BRACKET_H
#define BRACKET_H
#include <QStringList>
#include <functional>

enum BracketType{
    Round,
    Square,
    Curly
};
enum BracketSide{
    Opening,
    Closing
};

class bracket
{
public:
    bracket();
    bracket (const QStringList& code, int indexOfLineWithBracket, int position, bool order=true);
    bracket(BracketType currentType, BracketSide currentSide);
    BracketType getType() const;
    BracketSide getSide() const;
    int getPosition() const;
    int getLine() const;
    bool getOrder() const;

    void setOrder(bool order);

    bool operator==(const bracket& other) const
    {
        return (type == other.type && side == other.side &&
                numberOfLine == other.numberOfLine &&
                positionOfBraket == other.positionOfBraket && correctOfOrder == other.correctOfOrder);
    }

private:
    BracketType type;
    BracketSide side;
    int numberOfLine; //номер строки кода с данной скобкой
    int positionOfBraket; //позиция скобки в строке
    bool correctOfOrder; //правильность порядка скобки
};

inline size_t qHash(const bracket& key, size_t seed = 0) noexcept
{
    // Комбинируем хеши всех полей, которые участвуют в operator==
    return qHashMulti(seed,
                      static_cast<int>(key.getType()),
                      static_cast<int>(key.getSide()),
                      key.getLine(),
                      key.getPosition(),
                      key.getOrder());
}

#endif // BRACKET_H
